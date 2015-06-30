#include "Message_RobotCommand.hpp"

#include <sstream>

std::vector<unsigned char> Message_RobotCommand::serialize()
{
    std::string str;

    str.append("direction:");
    str.append(std::to_string(direction_));

    str.append("|");

    str.append("speed:");
    str.append(std::to_string(speed_));

    return std::vector<unsigned char>(str.begin(), str.end());
}

void Message_RobotCommand::unserialize(std::vector<unsigned char> const *data)
{
    auto str = std::string(data->begin(), data->end());

    if (str.find("direction:") != 0)
    {
        return;
    }

    // Find delimiter
    std::size_t pos_delim = str.find("|");

    // Direction is saved starting at 10th char to delimiter
    std::string str_direction = str.substr(10, pos_delim - 10);
    std::istringstream(str_direction) >> direction_;


    // Cut off everything up to the delimiter
    std::string str2 = str.substr(pos_delim + 1);

    if (str2.find("speed:") != 0)
    {
        return;
    }

    std::string str_speed = str2.substr(6);
    std::istringstream(str_speed) >> speed_;
}

