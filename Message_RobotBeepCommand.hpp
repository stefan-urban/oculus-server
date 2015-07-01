#ifndef MESSAGE_ROBOTBEEPCOMMAND_H
#define MESSAGE_ROBOTBEEPCOMMAND_H

#include <vector>
#include "Message.hpp"

class Message_RobotBeepCommand : public Message
{
public:
    enum { type_id = 12 };

    Message_RobotBeepCommand()
    {
    }

    Message_RobotBeepCommand(float direction, float speed)
        : direction_(direction)
        , speed_(speed)
    {
    }

    float direction() const
    {
        return direction_;
    }

    float speed() const
    {
        return speed_;
    }

    unsigned char get_type()
    {
        return (unsigned char) type_id;
    }

    std::vector<unsigned char> serialize();
    void unserialize(std::vector<unsigned char> const *str);

private:
    float direction_ = 0.0;
    float speed_ = 0.0;
};

#endif // MESSAGE_ROBOTBEEPCOMMAND_H
