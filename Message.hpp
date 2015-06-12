#ifndef EDVSMESSAGE_H
#define EDVSMESSAGE_H

#include <string>

class Message
{
public:
    virtual std::string serialize() = 0;
    virtual void unserialize(std::string const &str) = 0;
};

#endif // EDVSMESSAGE_H
