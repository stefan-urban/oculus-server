
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
    events_.clear();

    for (std::string token; std::getline(iss, token, '|'); )
    {
        Edvs::Event event = convert_string_to_event(token);

        // Some error
        if (event.id == 255)
        {
            continue;
        }

        events_.push_back(event);
    }
}


std::string Message_EventCollection::convert_event_to_string(const Edvs::Event e)
{
    std::ostringstream oss;

    std::string delim = "-";

    oss << std::dec << (int) e.id << delim;
    oss << std::dec << (int) e.x << delim;
    oss << std::dec << (int) e.y << delim;
    oss << std::dec << (int) e.parity << delim;
    oss << e.t;

    return oss.str();
}

Edvs::Event Message_EventCollection::convert_string_to_event(std::string str)
{
    Edvs::Event e;
    size_t pos = std::string::npos;
    int i = 0;

    do
    {
        // Find first occurance of delimiter
        pos = str.find("-");

        // Get string from start to delimiter
        std::string token = str.substr(0, pos);

        // Cut off token from source string
        str = str.substr(pos + 1);

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

    // Something went wrong!
    if (i != 5)
    {
        e.id = 255;

        return e;
    }

    return e;
}
