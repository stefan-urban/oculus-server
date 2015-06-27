#include "TcpServer.hpp"



void TcpServer::do_accept()
{
  acceptor_.async_accept(socket_,
      [this](boost::system::error_code ec)
      {
          if (!ec)
          {
              std::make_shared<TcpSession>(std::move(socket_), clients_, dispatcher_)->start();
          }

          do_accept();
      });
}
