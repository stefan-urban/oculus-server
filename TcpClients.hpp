#ifndef TCP_CLIENTS_H
#define TCP_CLIENTS_H

#include <set>

#include "TcpClient.hpp"
#include "TcpMessage.hpp"

class TcpClients
{
public:
    void join(TcpClient_ptr participant);
    void leave(TcpClient_ptr participant);
    void deliver(const TcpMessage& msg);

private:
    std::set<TcpClient_ptr> participants_;
    enum { max_recent_msgs = 100 };
    TcpMessageQueue recent_msgs_;
};


#endif // TCP_CLIENTS_H
