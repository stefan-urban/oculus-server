#ifndef EDVSMESSAGE_H
#define EDVSMESSAGE_H

#include <string>
#include <vector>

class Message
{
public:
    virtual unsigned char get_type() = 0;
    virtual std::vector<unsigned char> serialize() = 0;
    virtual void unserialize(std::vector<unsigned char> const *str) = 0;
};

#endif // EDVSMESSAGE_H
