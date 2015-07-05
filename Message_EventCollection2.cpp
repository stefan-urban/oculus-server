
#include <cstdlib>
#include <sstream>
#include <cstdint>
#include <string>
#include <boost/lexical_cast.hpp>

#include "Message_EventCollection2.hpp"


std::vector<unsigned char> Message_EventCollection2::serialize()
{
    std::vector<unsigned char> data;

    // Calculate number of bytes it takes to store all events
    size_t size = events_.size() * sizeof(message_edvs_event_t);
    data.resize(size);

    // And copy it over
    std::memcpy(data.data(), events_.data(), size);

    return data;
}

void Message_EventCollection2::unserialize(std::vector<unsigned char> const *data)
{
    // Number of bytes must a multiple of a single event size
    if (data->size() % sizeof(message_edvs_event_t))
    {
        return;
    }

    // Calculate the number of events
    size_t number_of_events = data->size() / sizeof(message_edvs_event_t);
    events_.resize(number_of_events);

    // And copy them over
    std::memcpy(events_.data(), data->data(), data->size());
}
