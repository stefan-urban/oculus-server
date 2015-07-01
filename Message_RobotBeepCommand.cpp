#include "Message_RobotBeepCommand.hpp"

#include <sstream>

std::vector<unsigned char> Message_RobotBeepCommand::serialize()
{
    // This command does not have data

    return std::vector<unsigned char>();
}

void Message_RobotBeepCommand::unserialize(std::vector<unsigned char> const * /* data */)
{

}

