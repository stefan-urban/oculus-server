#include "EdvsMessage.h"

#include <cstdio>

EdvsMessage::EdvsMessage()
{
}

void EdvsMessage::set_events(EdvsEventsCollection events)
{
    const int size_event = 14;
    int number_events = events.size();

    char tmp[size_event * number_events + 1] = "";

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

    body_length(std::strlen(tmp));
    std::memcpy(body(), tmp, body_length());
}
