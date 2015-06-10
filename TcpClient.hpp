#ifndef TCP_CLIENT_H
#define TCP_CLIENT_H

#include <boost/shared_ptr.hpp>

#include "TcpMessage.hpp"

class TcpClient
{
public:
  virtual ~TcpClient() {}
  virtual void deliver(const TcpMessage& msg) = 0;
};

typedef std::shared_ptr<TcpClient> TcpClient_ptr;


#endif // TCP_CLIENT_H
