#ifndef TCP_CLIENT_H
#define TCP_CLIENT_H

#include "Message.hpp"

#include <boost/shared_ptr.hpp>

static int next_id = 0;

class TcpClient
{
    int id;
public:
    TcpClient() : id(next_id++)
    {

    }

    int getId()
    {
        return id;
    }

    virtual ~TcpClient() {}
    virtual void deliver(Message *msg) = 0;
private:
};


typedef std::shared_ptr<TcpClient> TcpClient_ptr;


#endif // TCP_CLIENT_H
