#ifndef TCP_SERVER_HPP
#define TCP_SERVER_HPP

#include <boost/asio.hpp>

#include "TcpSession.hpp"
#include "TcpClients.hpp"
#include "Robot.hpp"

class TcpServer
{
public:
    TcpServer(boost::asio::io_service& io_service, const boost::asio::ip::tcp::endpoint& endpoint, Dispatcher *dispatcher)
        : acceptor_(io_service, endpoint)
        , socket_(io_service)
        , dispatcher_(dispatcher)
    {
        do_accept();
    }

    TcpClients* clients() {
        return &clients_;
    }

private:
    void do_accept();

    boost::asio::ip::tcp::acceptor acceptor_;
    boost::asio::ip::tcp::socket socket_;
    TcpClients clients_;
    Dispatcher *dispatcher_;
};


#endif // TCP_SERVER_HPP
