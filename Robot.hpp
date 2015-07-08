#ifndef ROBOT_H
#define ROBOT_H

#include <chrono>
#include <vector>

#include "SerialCommunication.hpp"
#include "vendor/dispatcher/Dispatcher.hpp"


class Robot : public DispatcherListener
{
public:
    Robot();
    ~Robot();

    void event(DispatcherEvent* event);

    void drive(int fwd, int swd, int ang);
    void stop();
    void beep();

    int duration_since_last_cmd_update();

private:
    const std::string path_ = std::string("/dev/ttyUSB0");
    SerialCommunication port_;

    std::chrono::steady_clock::time_point last_cmd_update_;
};

#endif // ROBOT_H
