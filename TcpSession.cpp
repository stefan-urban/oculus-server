
#include "TcpSession.hpp"
#include "Message_JoystickState.hpp"

void TcpSession::start()
{
    clients_.join(shared_from_this());
    do_read_header();
}

void TcpSession::deliver(TcpMessage& msg)
{
    // First prepare message
    msg.encode();

    bool write_in_progress = !write_msgs_.empty();
    write_msgs_.push_back(msg);
    if (!write_in_progress)
    {
        do_write();
    }
}

void TcpSession::do_read_header()
{
    auto self(shared_from_this());
    boost::asio::async_read(socket_,
        boost::asio::buffer(read_msg_.data(), TcpMessage::header_length),
        [this, self](boost::system::error_code ec, std::size_t /*length*/)
        {
            if (!ec && read_msg_.decode_header())
            {
                // Now we know how long the message is, finally read it
                do_read_body();
            }
            else
            {
                clients_.leave(shared_from_this());
            }
        });
}

void TcpSession::do_read_body()
{
    auto self(shared_from_this());
    boost::asio::async_read(socket_,
    boost::asio::buffer(read_msg_.body(), read_msg_.body_length()),
        [this, self](boost::system::error_code ec, std::size_t /*length*/)
        {
            if (!ec)
            {
                // Always is joystick message
                std::string const data = std::string(read_msg_.body());

                // Determine type
                size_t pos = data.find('|');

                if (pos == std::string::npos || pos < 2)
                {
                    return;
                }

                std::string type = data.substr(0, pos);

                // Pack new event and dispatch it
                auto e = DispatcherEvent(type, data.substr(pos + 1));
                dispatcher_->dispatch(&e);

                // And go back to reading the header
                do_read_header();
            }
            else
            {
                clients_.leave(shared_from_this());
            }
        });
}

void TcpSession::do_write()
{
    auto self(shared_from_this());
    boost::asio::async_write(socket_,
        boost::asio::buffer(write_msgs_.front().data(),
        write_msgs_.front().length()),
        [this, self](boost::system::error_code ec, std::size_t /*length*/)
        {
            if (!ec)
            {
                write_msgs_.pop_front();
                if (!write_msgs_.empty())
                {
                    do_write();
                }
            }
            else
            {
                clients_.leave(shared_from_this());
            }
        });
}
