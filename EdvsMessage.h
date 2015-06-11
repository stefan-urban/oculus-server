#ifndef EDVSMESSAGE_H
#define EDVSMESSAGE_H

#include "TcpMessage.hpp"
#include "EdvsEventsCollection.h"

class EdvsMessage : public TcpMessage
{
public:
    EdvsMessage()
    {
        type_ = 1;
    }

    void set_events(EdvsEventsCollection);
};

#endif // EDVSMESSAGE_H
