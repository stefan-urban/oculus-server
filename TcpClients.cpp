#include "TcpClients.hpp"
#include "TcpMessage.hpp"
#include "Message.hpp"

void TcpClients::join(TcpClient_ptr client)
{
    // Add client to list
    clients_.insert(client);

    // Deliver all recent messages
//    for (auto msg: recent_msgs_)
//        client->deliver(msg);

    std::cout << "join: #" << client->getId() << std::endl;
}

void TcpClients::leave(TcpClient_ptr client)
{
    clients_.erase(client);

    std::cout << "quit: #" << client->getId() << std::endl;
}

void TcpClients::deliver(TcpMessage& msg)
{
//    recent_msgs_.push_back(msg);
//    while (recent_msgs_.size() > max_recent_msgs)
//        recent_msgs_.pop_front();

    for (auto client: clients_)
        client->deliver(msg);
}
