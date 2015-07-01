#include "Robot.hpp"
#include "Message_RobotCommand.hpp"
#include "Message_RobotBeepCommand.hpp"
#include "vendor/edvstools/Edvs/edvs_impl.h"

#include <string>
#include <cmath>


Robot::Robot()
{
    fd_ = edvs_serial_open(path_.c_str(), 4000000);

    last_cmd_update_ = std::chrono::steady_clock::now();
    stop();
}

Robot::~Robot()
{
    edvs_serial_close(fd_);
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

        if (msg_robotcmd.speed() > 0.0)
        {
            drive(msg_robotcmd.direction(), msg_robotcmd.speed());
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

void Robot::drive(float direction, float speed)
{
    if (fd_ < 0)
    {
        return;
    }

    int fwd = (int)(cos(direction) * speed * 70.0);
    int swd = (int)(sin(direction) * speed * 70.0);

    std::string command;

    command.append("!D");
    command.append(std::to_string(fwd));
    command.append(",");
    command.append(std::to_string(swd));
    command.append(",");
    command.append("0");
    command.append("\n");

    edvs_serial_write(fd_, command.c_str(), command.size());
}

void Robot::stop()
{
    if (fd_ < 0)
    {
        return;
    }

    std::string command;
    command.append("!D0,0,0");
    command.append("\n");

    edvs_serial_write(fd_, command.c_str(), command.size());
}


void Robot::beep()
{
    if (fd_ < 0)
    {
        return;
    }

    std::string command;
    command.append("B");
    command.append("\n");

    std::cout << "Beep!" << std::endl;

    edvs_serial_write(fd_, command.c_str(), command.size());
}
