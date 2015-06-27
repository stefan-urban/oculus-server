#ifndef MESSAGE_JOYSTICKSTATE_H
#define MESSAGE_JOYSTICKSTATE_H

#include <vector>
#include "Message.hpp"

class Message_JoystickState : public Message
{
public:
    Message_JoystickState()
    {
    }

    Message_JoystickState(std::vector<bool> button_states, std::vector<int> axis_states)
        : button_states_(button_states)
        , axis_states_(axis_states)
    {
    }

    std::vector<bool> button_states()
    {
        return button_states_;
    }

    std::vector<int> axis_states()
    {
        return axis_states_;
    }


    std::string get_type()
    {
        return std::string("joystick");
    }

    std::string serialize();
    void unserialize(std::string const *str);

private:
    std::vector<bool> button_states_;
    std::vector<int> axis_states_;
};

#endif // MESSAGE_JOYSTICKSTATE_H
