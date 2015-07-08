#ifndef MESSAGE_ROBOTCOMMAND_H
#define MESSAGE_ROBOTCOMMAND_H

#include <vector>
#include "Message.hpp"

class Message_RobotCommand : public Message
{
public:
    enum { type_id = 11 };

    Message_RobotCommand()
    {
    }

    /**
     * Parameters from -70 to 70
     */
    Message_RobotCommand(int x_speed, int y_speed, int angular_speed)
        : x_speed_(x_speed)
        , y_speed_(y_speed)
        , angular_speed_(angular_speed)
    {
    }

    int x_speed() const
    {
        return x_speed_;
    }

    int y_speed() const
    {
        return y_speed_;
    }

    int angular_speed() const
    {
        return angular_speed_;
    }

    unsigned char get_type()
    {
        return (unsigned char) type_id;
    }

    std::vector<unsigned char> serialize();
    void unserialize(std::vector<unsigned char> const *str);

private:
    int x_speed_ = 0;
    int y_speed_ = 0;
    int angular_speed_ = 0;
};

#endif // MESSAGE_ROBOTCOMMAND_H
