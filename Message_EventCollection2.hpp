#ifndef EDVSMESSAGE_EVENTSWITTHOUTTIMESTAMPCOLLECTION_H
#define EDVSMESSAGE_EVENTSWITTHOUTTIMESTAMPCOLLECTION_H

#include "Message.hpp"

#include <string>
#include <stdint.h>

typedef struct {
    u_int16_t x, y;
    u_int8_t parity;
    u_int8_t id;
} message_edvs_event_t;


class Message_EventCollection2 : public Message
{
public:
    enum { type_id = 10 };

    void set_events(std::vector<message_edvs_event_t> events)
    {
        events_ = events;
    }

    std::vector<message_edvs_event_t> events()
    {
        return events_;
    }

    unsigned char get_type()
    {
        return (unsigned char) type_id;
    }

    void add_event(message_edvs_event_t e)
    {
        events_.push_back(e);
    }

    void add_event(unsigned char camera_id, unsigned char x, unsigned char y, bool parity)
    {
        message_edvs_event_t e;
        e.id = camera_id;
        e.x = x;
        e.y = y;
        e.parity = parity;

        add_event(e);
    }

    std::vector<unsigned char> serialize();
    void unserialize(std::vector<unsigned char> const *str);

private:
    std::vector<message_edvs_event_t> events_;
};


#endif // EDVSMESSAGE_EVENTSWITTHOUTTIMESTAMPCOLLECTION_H
