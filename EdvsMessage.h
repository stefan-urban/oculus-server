#ifndef EDVSMESSAGE_H
#define EDVSMESSAGE_H

#include "TcpMessage.hpp"
#include "EdvsEventsCollection.h"

class EdvsMessage : public TcpMessage
{
public:
    EdvsMessage();
    void set_events(EdvsEventsCollection);

private:
    std::string type = "1";
};

#endif // EDVSMESSAGE_H
