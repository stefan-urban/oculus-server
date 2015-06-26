#ifndef MESSAGE_JOYSTICKSTATE_H
#define MESSAGE_JOYSTICKSTATE_H

#include <vector>
#include "Message.hpp"

class Message_JoystickState : Message
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

    std::string serialize();
    void unserialize(std::string const *str);

private:
    std::vector<bool> button_states_;
    std::vector<int> axis_states_;
};

#endif // MESSAGE_JOYSTICKSTATE_H
