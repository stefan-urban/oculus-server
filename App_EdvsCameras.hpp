#ifndef APP_EDVSCAMERAS_HPP
#define APP_EDVSCAMERAS_HPP

#include "Application.hpp"
#include "Message_EventCollection2.hpp"

#include <string>
#include <boost/thread.hpp>

class App_EdvsCameras : Application
{
public:
    App_EdvsCameras(const std::string uri, int camera_id, std::vector<message_edvs_event_t> *events_buffer, boost::mutex *mutex);
    int run();
    void stop();

private:
    std::string uri_;
    int camera_id_;
    std::vector<message_edvs_event_t> *events_buffer_;
    boost::mutex *mutex_;

    int stop_ = 0;
};

#endif // APP_EDVSCAMERAS_HPP
