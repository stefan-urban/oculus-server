
#include <cstdlib>
#include <sstream>
#include <cstdint>
#include <boost/lexical_cast.hpp>

#include "Message_EventCollection.hpp"



void Message_EventCollection::set_events(EdvsEventsCollection e)
{
    events_ = e;
}

std::vector<unsigned char> Message_EventCollection::serialize()
{
    std::vector<unsigned char> data;

    // First timestamp will be stored at the first 4 byte
    u_int64_t first_timestamp = events_.front().t;

    data.push_back((first_timestamp >> (3 * 8)) & 0xFF);
    data.push_back((first_timestamp >> (2 * 8)) & 0xFF);
    data.push_back((first_timestamp >> (1 * 8)) & 0xFF);
    data.push_back((first_timestamp >> (0 * 8)) & 0xFF);


    // Now store events with only a relative timediff
    for (auto it = events_.begin(); it != events_.end(); ++it)
    {
        u_int16_t diff = (u_int16_t) (it->t - first_timestamp);

        data.push_back((unsigned char) ((it->id << 1) | (it->parity & 0x01)));
        data.push_back((unsigned char) it->x);
        data.push_back((unsigned char) it->y);
        data.push_back((unsigned char) ((diff >> 8) & 0xFF));
        data.push_back((unsigned char) (diff & 0xFF));
    }

    return data;
}


void Message_EventCollection::unserialize(std::vector<unsigned char> const *data)
{
    if (data->size() < 4)
    {
        return;
    }

    // First four bytes are timestamp
    u_int64_t first_timestamp = 0;

    for (size_t i = 0; i < 4; i++)
    {
        first_timestamp |= data->at(i) << ((3 - i) * 8);
    }

    // Now do all others
    if ((data->size() - 4) % 5)
    {
        // Somethings wrong
        return;
    }

    for (size_t i = 4; i < data->size() - 4; i += 5)
    {
        Edvs::Event e;

        // First byte is id and parity
        e.id = (data->at(i) >> 1) & 0x7F;
        e.parity = data->at(i) & 0x01;

        // Second and third byte are coordinates
        e.x = data->at(i + 1);
        e.y = data->at(i + 2);

        // Fourth and fifth byte are difference to first timestamp
        u_int16_t diff = 0;
        diff |= data->at(i + 3) << 8;
        diff |= data->at(i + 4);

        e.t = first_timestamp + (u_int64_t) diff;

        // And finally add event
        events_.push_back(e);
    }
}
