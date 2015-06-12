#ifndef EDVSEVENTSCOLLECTION_H
#define EDVSEVENTSCOLLECTION_H

#include "vendor/edvstools/Edvs/EventStream.hpp"

class EdvsEventsCollection : public std::vector<Edvs::Event>
{
public:
    EdvsEventsCollection();
};

#endif // EDVSEVENTSCOLLECTION_H
