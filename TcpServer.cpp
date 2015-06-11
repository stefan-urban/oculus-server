#include "TcpServer.hpp"


TcpServer::TcpServer(boost::asio::io_service& io_service,
    const boost::asio::ip::tcp::endpoint& endpoint)
  : acceptor_(io_service, endpoint),
    socket_(io_service)
{
    do_accept();
}

void TcpServer::do_accept()
{
  acceptor_.async_accept(socket_,
      [this](boost::system::error_code ec)
      {
          if (!ec)
          {
              std::make_shared<TcpSession>(std::move(socket_), clients_)->start();
          }

          do_accept();
      });
}
