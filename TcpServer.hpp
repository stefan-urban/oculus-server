#ifndef TCP_SERVER_HPP
#define TCP_SERVER_HPP

#include <boost/asio.hpp>

#include "TcpSession.hpp"
#include "TcpClients.hpp"

class TcpServer
{
public:
  TcpServer(boost::asio::io_service& io_service,
      const boost::asio::ip::tcp::endpoint& endpoint);

  TcpClients* clients() {
      return &clients_;
  }

private:
  void do_accept();

  boost::asio::ip::tcp::acceptor acceptor_;
  boost::asio::ip::tcp::socket socket_;
  TcpClients clients_;
};


#endif // TCP_SERVER_HPP
