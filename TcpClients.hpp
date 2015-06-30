#ifndef TCP_CLIENTS_H
#define TCP_CLIENTS_H

#include <set>

#include "TcpClient.hpp"


class TcpClients
{
public:
    void join(TcpClient_ptr participant);
    void leave(TcpClient_ptr participant);
    void deliver(Message *msg);

    std::size_t clients_size()
    {
        return clients_.size();
    }

private:
    std::set<TcpClient_ptr> clients_;
    enum { max_recent_msgs = 100 };
};


#endif // TCP_CLIENTS_H
