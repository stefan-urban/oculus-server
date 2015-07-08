#include "Robot.hpp"
#include "Message_RobotCommand.hpp"
#include "Message_RobotBeepCommand.hpp"
#include "vendor/edvstools/Edvs/edvs_impl.h"

#include <string>
#include <cmath>


Robot::Robot()
{
    port_.open(path_);
    stop();

    last_cmd_update_ = std::chrono::steady_clock::now();
}

Robot::~Robot()
{
    stop();
    port_.close();
}

int Robot::duration_since_last_cmd_update()
{
    auto t2 = std::chrono::steady_clock::now();
    return std::chrono::duration_cast<std::chrono::milliseconds>(t2 - last_cmd_update_).count();
}

void Robot::event(DispatcherEvent* event)
{
    if (event->type() == Message_RobotCommand::type_id)
    {
        Message_RobotCommand msg_robotcmd;

        msg_robotcmd.unserialize(event->data());

        if (std::abs(msg_robotcmd.x_speed()) > 0 || std::abs(msg_robotcmd.y_speed()) > 0)
        {
            drive(msg_robotcmd.x_speed(), msg_robotcmd.y_speed(), msg_robotcmd.angular_speed());
        }
        else
        {
            stop();
        }

        last_cmd_update_ = std::chrono::steady_clock::now();
    }
    else if (event->type() == Message_RobotBeepCommand::type_id)
    {
        beep();
    }
}

void Robot::drive(int fwd, int swd, int ang)
{
    std::string command;

    command.append("!D");
    command.append(std::to_string(fwd));
    command.append(",");
    command.append(std::to_string(swd));
    command.append(",");
    command.append(std::to_string(ang));
    command.append("\n");

    port_.write(command.c_str(), command.size());
    //edvs_serial_write(fd_, command.c_str(), command.size());
}

void Robot::stop()
{
    std::string command;
    command.append("!D0,0,0");
    command.append("\n");

    port_.write(command.c_str(), command.size());
    //edvs_serial_write(fd_, command.c_str(), command.size());
}


void Robot::beep()
{
    std::string command;
    command.append("B");
    command.append("\n");

    port_.write(command.c_str(), command.size());
    //edvs_serial_write(fd_, command.c_str(), command.size());
}
