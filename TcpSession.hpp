#ifndef TCP_SESSION_H
#define TCP_SESSION_H

#include <boost/asio.hpp>

#include "TcpClients.hpp"
#include "TcpMessage.hpp"

class TcpSession
  : public TcpClient,
    public std::enable_shared_from_this<TcpSession>
{
public:
    TcpSession(boost::asio::ip::tcp::socket socket, TcpClients& room);
    void start();
    void deliver(const TcpMessage& msg);
private:
    void do_read_header();
    void do_read_body();
    void do_write();

    boost::asio::ip::tcp::socket socket_;
    TcpClients& clients_;
    TcpMessage read_msg_;
    TcpMessageQueue write_msgs_;
};

#endif // TCP_SESSION_H
