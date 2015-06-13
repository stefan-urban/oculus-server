
#include <cstdlib>
#include <sstream>
#include <stdint.h>

#include "Message_EventCollection.hpp"



void Message_EventCollection::set_events(EdvsEventsCollection e)
{
    events_ = e;
}

std::string Message_EventCollection::serialize()
{
    std::string str;

    for(const Edvs::Event& e : events_)
    {
        str.append(convert_event_to_string(e));
        str.append("|");
    }

    return str;
}


void Message_EventCollection::unserialize(std::string const *str)
{
    std::stringstream iss(*str);

    for (std::string token; std::getline(iss, token, '|'); )
    {
        events_.push_back(convert_string_to_event(token));
    }
}


std::string Message_EventCollection::convert_event_to_string(const Edvs::Event e)
{
    char buffer[100];
    snprintf(buffer, 100, "%02u-%03u-%03u-%1u-%015u", e.id, e.x, e.y, e.parity, e.t);

    return std::string(buffer);
}

Edvs::Event Message_EventCollection::convert_string_to_event(const std::string str)
{
    Edvs::Event e;
    std::stringstream iss(str);

    int i = 0;
    for (std::string token; std::getline(iss, token, '-'); )
    {
        switch(i)
        {
        case 0: // id
            e.id = (u_int8_t) std::atoi(token.c_str());
            break;

        case 1: // x
            e.x = (u_int16_t) std::atoi(token.c_str());
            break;

        case 2: // y
            e.y = (u_int16_t) std::atoi(token.c_str());
            break;

        case 3: // parity
            e.parity = (u_int8_t) std::atoi(token.c_str());
            break;

        case 4: // time
            e.t = (u_int64_t) std::atoi(token.c_str());
            break;

        }

        i++;
    }

    return e;
}
