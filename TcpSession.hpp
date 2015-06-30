#ifndef TCP_SESSION_H
#define TCP_SESSION_H

#include <deque>
#include <vector>
#include <boost/asio.hpp>

#include "TcpClients.hpp"
#include "Message.hpp"
#include "Robot.hpp"
#include "vendor/dispatcher/Dispatcher.hpp"

class TcpSession
  : public TcpClient,
    public std::enable_shared_from_this<TcpSession>
{
public:
    enum { header_length = 4 };

    TcpSession(boost::asio::ip::tcp::socket socket, TcpClients& clients, Dispatcher *dispatcher)
        : socket_(std::move(socket))
        , clients_(clients)
        , dispatcher_(dispatcher)
    {
        /*
        if (TcpMessage::header_length > 4)
        {
            throw std::exception("TCP message header length must be less or equal to 4");
        }
        */

        read_header_.resize(header_length);
    }

    void start();
    void deliver(Message *msg);
private:
    void do_read_header();
    void do_read_body();
    void do_write();

    boost::asio::ip::tcp::socket socket_;
    TcpClients& clients_;

    Dispatcher *dispatcher_;

    std::vector<unsigned char> read_header_;
    std::vector<unsigned char> read_body_;
    std::deque<std::vector<unsigned char>> write_buffer_;
};

#endif // TCP_SESSION_H
