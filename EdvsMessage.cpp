#include "EdvsMessage.h"

#include <cstdio>

void EdvsMessage::set_events(EdvsEventsCollection events)
{
    const int size_event = 14;
    int number_events = events.size();

    if (number_events < 1)
    {
        return;
    }

    char tmp[size_event * number_events + 1] = "";
    tmp[size_event * number_events] = '\0';

    int i = 0;
    for (const Edvs::Event& event : events)
    {
        tmp[0 + size_event * i] = (event.t >> 8 * 0) & 0xFF;
        tmp[1 + size_event * i] = (event.t >> 8 * 1) & 0xFF;
        tmp[2 + size_event * i] = (event.t >> 8 * 2) & 0xFF;
        tmp[3 + size_event * i] = (event.t >> 8 * 3) & 0xFF;
        tmp[4 + size_event * i] = (event.t >> 8 * 4) & 0xFF;
        tmp[5 + size_event * i] = (event.t >> 8 * 5) & 0xFF;
        tmp[6 + size_event * i] = (event.t >> 8 * 6) & 0xFF;
        tmp[7 + size_event * i] = (event.t >> 8 * 7) & 0xFF;

        tmp[8 + size_event * i] = (event.x >> 8 * 0) & 0xFF;
        tmp[9 + size_event * i] = (event.x >> 8 * 1) & 0xFF;
        tmp[10 + size_event * i] = (event.y >> 8 * 0) & 0xFF;
        tmp[11 + size_event * i] = (event.y >> 8 * 1) & 0xFF;

        tmp[12 + size_event * i] = event.parity;
        tmp[13 + size_event * i] = event.id;

        i++;
    }

    body_length(size_event * number_events);
    std::memcpy(body(), tmp, body_length());
}


EdvsEventsCollection EdvsMessage::get_events()
{
    EdvsEventsCollection events;
    int size = body_length();

    // Number of bytes has to match size of events
    if (size % size_event)
    {
        return events;
    }

    int number_events = size / size_event;

    // Read the data to a local variable
    char tmp[size + 1] = "";
    tmp[size] = '\0';

    std::memcpy(tmp, body(), size);

    // Extract events
    for (int i = 0; i < number_events; i++)
    {
        Edvs::Event event;

        event.t = (long int) tmp[0 + size_event * i] << (8 * 0);
        event.t |= (long int) tmp[1 + size_event * i] << (8 * 1);
        event.t |= (long int) tmp[2 + size_event * i] << (8 * 2);
        event.t |= (long int) tmp[3 + size_event * i] << (8 * 3);
        event.t |= (long int) tmp[4 + size_event * i] << (8 * 4);
        event.t |= (long int) tmp[5 + size_event * i] << (8 * 5);
        event.t |= (long int) tmp[6 + size_event * i] << (8 * 6);
        event.t |= (long int) tmp[7 + size_event * i] << (8 * 7);

        event.x = tmp[8 + size_event * i] << (8 * 0);
        event.x = tmp[9 + size_event * i] << (8 * 1);
        event.y = tmp[10 + size_event * i] << (8 * 0);
        event.y = tmp[11 + size_event * i] << (8 * 1);

        event.parity = tmp[12 + size_event * i];
        event.id = tmp[13 + size_event * i];

        events.push_back(event);
    }

    return events;
}
