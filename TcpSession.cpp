#include "TcpSession.hpp"


void TcpSession::start()
{
    clients_.join(shared_from_this());
    do_read_header();
}

void TcpSession::deliver(Message *msg)
{
    unsigned char type = msg->get_type();
    std::vector<unsigned char> data = msg->serialize();

    data.insert(data.begin(), type);


    bool write_in_progress = !write_buffer_.empty();
    write_buffer_.push_back(data);

    if (!write_in_progress)
    {
        do_write();
    }
}

void TcpSession::do_read_header()
{
    auto self(shared_from_this());
    boost::asio::async_read(socket_, boost::asio::buffer(read_header_),
        [this, self](boost::system::error_code ec, std::size_t /*length*/)
        {
            if (!ec)
            {
                unsigned long body_size;

                for (size_t i = 0; i < header_length; i++)
                {
                    body_size |= read_header_[i] << ((header_length - i - 1) * 8);
                }

                read_body_.resize(body_size);

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
    boost::asio::async_read(socket_, boost::asio::buffer(read_body_),
        [this, self](boost::system::error_code ec, std::size_t /*length*/)
        {
            if (!ec)
            {
                // Determine type
                unsigned char type = read_body_[0];

                // Erase type from data block
                read_body_.erase(read_body_.begin());

                // Pack new event and dispatch it
                auto e = DispatcherEvent(type, &read_body_);
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
    boost::asio::async_write(socket_, boost::asio::buffer(write_buffer_.front()),
        [this, self](boost::system::error_code ec, std::size_t /*length*/)
        {
            if (!ec)
            {
                // Delete transmitted message
                write_buffer_.pop_front();

                // Continue transmitting if there are still messages left
                if (!write_buffer_.empty())
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
