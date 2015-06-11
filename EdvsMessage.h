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
    EdvsEventsCollection get_events();

private:
    const int size_event = 14;
    int type_;
};

#endif // EDVSMESSAGE_H
