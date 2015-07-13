#ifndef APP_ROBOT_HPP
#define APP_ROBOT_HPP

#include "Application.hpp"
#include "Robot.hpp"

class App_Robot : Application
{
public:
    App_Robot(Robot *robot);
    int run();
    void stop();

private:
    int stop_ = 0;
    Robot *robot_;
};

#endif // APP_ROBOT_HPP
