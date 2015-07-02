#include "TcpClients.hpp"
#include "Message.hpp"

void TcpClients::join(TcpClient_ptr client)
{
    // Add client to list
    clients_.insert(client);

    std::cout << "Client joined: #" << client->getId() << std::endl;
}

void TcpClients::leave(TcpClient_ptr client)
{
    clients_.erase(client);

    std::cout << "Client quit: #" << client->getId() << std::endl;
}

void TcpClients::deliver(Message *msg)
{
    for (auto client: clients_)
    {
        client->deliver(msg);
    }
}
