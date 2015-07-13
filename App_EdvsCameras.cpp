#include "App_EdvsCameras.hpp"

#include <unistd.h>
#include <iostream>
#include "SerialCommunication.hpp"

App_EdvsCameras::App_EdvsCameras(const std::string uri, int camera_id, std::vector<message_edvs_event_t> *events_buffer, boost::mutex *mutex)
    : uri_(uri)
    , camera_id_(camera_id)
    , events_buffer_(events_buffer)
    , mutex_(mutex)
{

}


int App_EdvsCameras::run()
{
    SerialCommunication port;

    if (!port.open(uri_))
    {
        std::cout << "connection to " << uri_ << " failed" << std::endl;
        return -1;
    }

    std::cout << "connected to " << uri_ << std::endl;

    // Clear out buffer
    std::string cmd = "??\n";

    port.write(cmd.c_str(), 3);
    usleep(10 * 1000);

    port.write(cmd.c_str(), 3);
    usleep(10 * 1000);

    // Send start command
    cmd = "E+\n";
    if (port.write(cmd.c_str(), 3) == -1)
    {
        std::cout << "starting command failed" << std::endl;
        return -1;
    }

    //std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();

    while (stop_ == 0)
    {
        ssize_t size = 0;

        // Read all pending events
        while(stop_ == 0)
        {
            char buffer[2];
            size = port.read(buffer, 2);

            if (size != 2)
            {
                break;
            }

            if (!(buffer[0] & 0x80))
            {
                port.read(buffer, 1);
                continue;
            }

            if (events_buffer_->size() > 1500)
            {
                continue;
            }

            // Create event
            message_edvs_event_t event;

            event.id = camera_id_;
            event.x = buffer[0] & 0x7F;
            event.y = buffer[1] & 0x7F;
            event.parity = (buffer[1] & 0x80) ? 1 : 0;

            //auto duration = std::chrono::steady_clock::now() - start;
            //event.t = std::chrono::duration_cast<std::chrono::microseconds>(duration).count() + 1000000000LL;

            mutex_->lock();
            events_buffer_->push_back(event);
            mutex_->unlock();
        }

        usleep(30 * 1000);
    }

    return 0;
}

void App_EdvsCameras::stop()
{
    stop_ = 1;
}
