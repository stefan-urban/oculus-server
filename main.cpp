#include <iostream>
#include <deque>
#include <set>
#include <list>
#include <random>
#include <time.h>
#include <vector>
#include <chrono>
#include <boost/asio.hpp>
#include <boost/thread.hpp>

#include "Robot.hpp"
#include "TcpServer.hpp"
#include "SerialCommunication.hpp"
#include "vendor/edvstools/Edvs/EventStream.hpp"
#include "vendor/dispatcher/Dispatcher.hpp"

#include "App_EdvsCameras.hpp"
#include "App_Robot.hpp"

#include "Message_EventCollection2.hpp"
#include "Message_RobotCommand.hpp"
#include "Message_RobotBeepCommand.hpp"
#include "Message_JoystickEvent.hpp"

//#define DEBUG


int global_stop = 0;


const std::vector<std::string> uris = {
//    std::string("/dev/ttyUSB0"),
//    std::string("/dev/ttyUSB1"),

    /*
    std::string("/dev/ttyUSB2"),
    std::string("/dev/ttyUSB3"),
    std::string("/dev/ttyUSB4"),
    std::string("/dev/ttyUSB5"),
    std::string("/dev/ttyUSB6"),
    std::string("/dev/ttyUSB7"),
    */

//    std::string("10.162.177.202:7002"),
//    std::string("10.162.177.202:7003"),
//    std::string("10.162.177.202:7004"),
//    std::string("10.162.177.202:7005"),
//    std::string("10.162.177.202:7006"),
//    std::string("10.162.177.202:7007"),

    std::string("/dev/edvs_camera_debug_7001"),
    std::string("/dev/edvs_camera_debug_7002"),
    std::string("/dev/edvs_camera_debug_7003"),
    std::string("/dev/edvs_camera_debug_7004"),
    std::string("/dev/edvs_camera_debug_7005"),
    std::string("/dev/edvs_camera_debug_7006"),

//    std::string("127.0.0.1:7002"),
//    std::string("127.0.0.1:7003"),
//    std::string("127.0.0.1:7004"),
//    std::string("127.0.0.1:7005"),
//    std::string("127.0.0.1:7006"),
//    std::string("127.0.0.1:7007"),

//    std::string("10.162.177.202:7006")
//    std::string("/dev/ttyUSB1?baudrate=4000000"),
//    std::string("/dev/ttyUSB2?baudrate=4000000")
};

std::vector<message_edvs_event_t> events_buffer;
boost::mutex mutex;

void edvs_app(const std::string uri, int camera_id)
{
    auto app = App_EdvsCameras(uri, camera_id, &events_buffer, &mutex);

    app.run();
}

void edvs_demo_app()
{
    //std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();

    while (global_stop == 0)
    {
        mutex.lock();

        for (int i = 0; i < 1; i++)
        {
            message_edvs_event_t e;

            e.id = rand() % 7;
            e.x = rand() % 128;
            e.y = rand() % 128;
            e.parity = rand() % 2;

            // Contious timestamp in us (no clear time reference)
            //auto duration = std::chrono::steady_clock::now() - start;
            //e.t = std::chrono::duration_cast<std::chrono::microseconds>(duration).count() + 100000000LL;

            //std::cout << "time: " << e.t << std::endl;

            events_buffer.push_back(e);
        }

        mutex.unlock();

        // Wait for 1 s
        usleep(400 * 1000);
    }
}

void edvs_transmit_app(TcpServer *server)
{
    int time = 0;
    unsigned long int number_of_events = 0;

    while (global_stop == 0)
    {
        if (events_buffer.size() > 0)
        {
            mutex.lock();

            // Deliver all read events to connected devices
            Message_EventCollection2 msg;
            msg.set_events(events_buffer);

            server->clients()->deliver(&msg);

            // Count events
            number_of_events += events_buffer.size();

            // Send time diff between first and last
//            std::cout << "time diff : " << std::to_string(msg.events().back().t - msg.events().front().t) << std::endl;
//            std::cout << "send: " << std::to_string(msg.events().back().t) << std::endl;

            // After sending delete everything
            events_buffer.clear();

            mutex.unlock();
        }

        usleep(30 * 1000);
        time += 30;

        if (time >= 1000)
        {
            std::cout << "Send rate: " << number_of_events << " events/s" << std::endl;

            number_of_events = 0;
            time = 0;
        }
    }
}

int robot_movement_control_app(Robot *robot)
{
    auto app = App_Robot(robot);

    app.run();
}

int main(int /*argc*/, char** /*argv[]*/)
{
    std::cout << "oculus-server v1" << std::endl;

    boost::asio::io_service io_service;
    Robot robot;

    // Setup dispatcher
    auto dispatcher = new Dispatcher();
    dispatcher->addListener(&robot, Message_RobotCommand::type_id);
    dispatcher->addListener(&robot, Message_RobotBeepCommand::type_id);
    dispatcher->addListener(&robot, Message_JoystickEvent::type_id);

    // Setup TCP server
    boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::tcp::v4(), 4000);
    TcpServer server(io_service, endpoint, dispatcher);


    // Start threads
#ifndef DEBUG
    std::vector<boost::thread*> edas;

    int camera_id = 0;
    for (auto& uri : uris)
    {
        boost::thread eda(edvs_app, uri, camera_id++);
        edas.push_back(&eda);
    }
#else
    boost::thread eda(edvs_demo_app);
#endif

    boost::thread eta(edvs_transmit_app, &server);
    boost::thread rca(robot_movement_control_app, &robot);

    io_service.run();


    // Wait for all threads to finish
#ifndef DEBUG
    for (boost::thread* eda : edas)
    {
        eda->join();
    }
#else
    eda.join();
#endif
    eta.join();
    rca.join();

    return 0;
}

