#include "Robot.hpp"
#include "Message_JoystickState.hpp"
#include <string>

Robot::Robot()
{
}

void Robot::event(DispatcherEvent event)
{
    if (event.type().compare("joystick") != 0)
    {
        return;
    }

    Message_JoystickState msg_joystick;

    std::string data = event.data();
    msg_joystick.unserialize(&data);

    update_states(msg_joystick.button_states(), msg_joystick.axis_states());

}

void Robot::update_states(std::vector<bool> button_states, std::vector<int> axis_states)
{
    // Buttons
}

