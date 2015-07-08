#include "Message_RobotCommand.hpp"

#include <sstream>

std::vector<unsigned char> Message_RobotCommand::serialize()
{
    std::string str;

    str.append("x:");
    str.append(std::to_string(x_speed_));

    str.append("|");

    str.append("y:");
    str.append(std::to_string(y_speed_));

    str.append("|");

    str.append("a:");
    str.append(std::to_string(angular_speed_));

    return std::vector<unsigned char>(str.begin(), str.end());
}

void Message_RobotCommand::unserialize(std::vector<unsigned char> const *data)
{
    auto str = std::string(data->begin(), data->end());

    if (str.find("x:") != 0)
    {
        return;
    }

    // Find delimiter
    std::size_t pos_delim = str.find("|");

    // Direction is saved starting at 10th char to delimiter
    std::string str_x_speed = str.substr(2, pos_delim - 2);
    std::istringstream(str_x_speed) >> x_speed_;


    // Cut off everything up to the delimiter
    std::string str2 = str.substr(pos_delim + 1);

    if (str2.find("y:") != 0)
    {
        return;
    }

    std::string str_y_speed = str2.substr(2);
    std::istringstream(str_y_speed) >> y_speed_;

    // Cut off everything up to the delimiter
    pos_delim = str2.find("|");
    std::string str3 = str2.substr(pos_delim + 1);

    if (str3.find("a:") != 0)
    {
        return;
    }

    std::string str_angular_speed = str3.substr(2);
    std::istringstream(str_angular_speed) >> angular_speed_;
}

