
#include "TcpClients.hpp"


void TcpClients::join(TcpClient_ptr participant)
{
    participants_.insert(participant);
    for (auto msg: recent_msgs_)
        participant->deliver(msg);
}

void TcpClients::leave(TcpClient_ptr participant)
{
    participants_.erase(participant);
}

void TcpClients::deliver(const TcpMessage& msg)
{
    recent_msgs_.push_back(msg);
    while (recent_msgs_.size() > max_recent_msgs)
        recent_msgs_.pop_front();

    for (auto participant: participants_)
        participant->deliver(msg);
}
