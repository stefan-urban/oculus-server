
#include <cstdlib>
#include <sstream>
#include <cstdint>
#include <boost/lexical_cast.hpp>

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

Edvs::Event Message_EventCollection::convert_string_to_event(std::string str)
{
    Edvs::Event e;
    size_t pos = std::string::npos;

    do
    {
        // Find first occurance of delimiter
        pos = str.find("-");

        // Get string from start to delimiter
        std::string token = str.substr(0, pos);

        // Cut off token from source string
        str = str.substr(pos + 1);

        int i = 0;

        // Only do something if token is containing characters, this
        // is because two values can have more than one delimiter in
        // between them
        if (token.size() > 0)
        {
            switch (i)
            {
            case 0:
                e.id = std::atoi(token.c_str());
                break;
            case 1:
                e.x = std::atoi(token.c_str());
                break;
            case 2:
                e.y = std::atoi(token.c_str());
                break;
            case 3:
                e.parity = std::atoi(token.c_str());
                break;
            case 4:
                std::istringstream iss(token.c_str());
                iss >> e.t;
                break;
            }

            i++;
        }
    }
    while (pos != std::string::npos);

    return e;
}
