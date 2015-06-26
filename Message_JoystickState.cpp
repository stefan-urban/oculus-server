#include "Message_JoystickState.hpp"

#include <sstream>

std::string Message_JoystickState::serialize()
{
    std::string str = "button:";

    for(bool bs : button_states_)
    {
        str.append(bs ? "1" : "0");
    }

    str.append("|");
    str.append("axis:");

    for(int axis : axis_states_)
    {
        str.append(std::to_string(axis));
        str.append(":");
    }

    return str;
}

void Message_JoystickState::unserialize(std::string const *str)
{
    button_states_.clear();
    axis_states_.clear();

    if (str->find("button:") != 0)
    {
        return;
    }

    // Find delimiter
    size_t pos_delim = str->find("|");

    // Number of buttons is the length between label and delimiter
    size_t number_of_buttons = pos_delim - 7;
    button_states_.resize(number_of_buttons);

    for (size_t i = 0; i < number_of_buttons; i++)
    {
        button_states_[i] = (str->substr(7 + i, 1) == "1") ? true : false;
    }

    // Find axis
    std::stringstream data(str->substr(pos_delim + 1 + 5));

    if (data.str().size() <= 5)
    {
        return;
    }

    std::string token;
    while(std::getline(data, token, ':'))
    {
        int axis;
        std::istringstream(token) >> axis;

        axis_states_.push_back(axis);
    }
}
