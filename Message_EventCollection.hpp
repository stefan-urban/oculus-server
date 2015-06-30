#ifndef EDVSMESSAGE_EVENTSCOLLECTION_H
#define EDVSMESSAGE_EVENTSCOLLECTION_H


#include "Message.hpp"
#include "EdvsEventsCollection.hpp"

#include <string>


class Message_EventCollection : public Message
{
public:
    enum { type_id = 10 };

    void set_events(EdvsEventsCollection e);

    EdvsEventsCollection events()
    {
        return events_;
    }

    unsigned char get_type()
    {
        return (unsigned char) type_id;
    }

    std::vector<unsigned char> serialize();
    void unserialize(std::vector<unsigned char> const *str);

private:

    EdvsEventsCollection events_;

    std::string convert_event_to_string(Edvs::Event);
    Edvs::Event convert_string_to_event(std::string str);

};


#endif // EDVSMESSAGE_EVENTSCOLLECTION_H
