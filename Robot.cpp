#include "Robot.hpp"
#include "Message_RobotCommand.hpp"
#include "vendor/edvstools/Edvs/edvs_impl.h"

#include <string>
#include <cmath>


Robot::Robot()
{
    fd_ = edvs_serial_open(path_.c_str(), 4000000);

    last_cmd_update_ = std::chrono::steady_clock::now();
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

void Robot::event(DispatcherEvent event)
{
    Message_RobotCommand msg_robotcmd;

    std::string data = event.data();
    msg_robotcmd.unserialize(&data);

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

void Robot::drive(float direction, float speed)
{
    if (fd_ < 0)
    {
        return;
    }

    std::string command;

    command.append("!D");
    command.append(std::to_string((int) (direction * 180.0 / M_PI)));
    command.append(",");
    command.append(std::to_string((int) (speed * 100.0)));


    edvs_serial_write(fd_, command.c_str(), command.size());
}

void Robot::stop()
{
    std::string command;
    command.append("!S");

    edvs_serial_write(fd_, command.c_str(), command.size());
}


void Robot::beep()
{
    std::string command;
    command.append("B");

    edvs_serial_write(fd_, command.c_str(), command.size());
}
