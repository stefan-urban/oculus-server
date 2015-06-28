#ifndef MESSAGE_ROBOTCOMMAND_H
#define MESSAGE_ROBOTCOMMAND_H

#include <vector>
#include "Message.hpp"

class Message_RobotCommand : public Message
{
public:
    Message_RobotCommand()
    {
    }

    Message_RobotCommand(float direction, float speed)
        : direction_(direction)
        , speed_(speed)
    {
    }

    std::string get_type()
    {
        return std::string("robotcmd");
    }

    std::string serialize();
    void unserialize(std::string const *str);

private:
    float direction_ = 0.0;
    float speed_ = 0.0;
};

#endif // MESSAGE_ROBOTCOMMAND_H
