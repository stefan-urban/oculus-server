#include "App_Robot.hpp"

#include <unistd.h>

App_Robot::App_Robot(Robot *robot)
    : robot_(robot)
{

}

int App_Robot::run()
{
    while (stop_ == 0)
    {
        // Timeout for client robot control, 500 ms
        if (robot_->duration_since_last_cmd_update() > 500)
        {
            static int counter = 0;

            robot_->stop();

            if (counter++ % 50 == 0)
            {
                robot_->beep();
            }
        }

        // Sleep 0.2 seconds
        usleep(500 * 1000);
    }

    return 0;
}

void App_Robot::stop()
{
    stop_ = 1;
}
