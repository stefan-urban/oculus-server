#include <iostream>
#include <deque>
#include <set>
#include <list>
#include <random>
#include <time.h>
#include <vector>
#include <boost/asio.hpp>
#include <boost/thread.hpp>

#include "Robot.hpp"
#include "TcpServer.hpp"
#include "EdvsEventsCollection.hpp"
#include "Message_EventCollection.hpp"
#include "Message_RobotCommand.hpp"
#include "vendor/edvstools/Edvs/EventStream.hpp"
#include "vendor/dispatcher/Dispatcher.hpp"



//#define DEBUG


int global_stop = 0;


EdvsEventsCollection events_buffer;
boost::mutex mutex;

const std::vector<std::string> uris = {
    std::string("127.0.0.1:7001"),
    std::string("127.0.0.1:7002"),
    std::string("127.0.0.1:7003"),
    std::string("127.0.0.1:7004"),
    std::string("127.0.0.1:7005"),
    std::string("127.0.0.1:7006")
//    std::string("10.162.177.202:7006")
//    std::string("/dev/ttyUSB1?baudrate=4000000"),
//    std::string("/dev/ttyUSB2?baudrate=4000000")
};

void edvs_app(const std::string uri, int camera_id)
{
    auto stream = Edvs::OpenEventStream(uri);

    if (!stream->is_open() ||!stream->is_live())
    {
        std::cout << "Could not open stream: " << uri << std::endl;
        return;
    }

    while (global_stop == 0)
    {
        auto events = stream->read();

        mutex.lock();

        for(const Edvs::Event& e : events) {
            //std::cout << "id: " << e.id << "\t x:" << e.x << "\t y:" << e.y << std::endl;
            events_buffer.push_back(e);
            events_buffer.back().id = camera_id;
        }

        mutex.unlock();

        // Wait for 5 ms
        usleep(5 * 1000);
    }
}

void edvs_demo_app()
{
    while (global_stop == 0)
    {
        mutex.lock();

        for (int i = 0; i < 1000; i++)
        {
            Edvs::Event e;

            e.id = rand() % 7;
            e.x = rand() % 128;
            e.y = rand() % 128;
            e.parity = rand() % 2;

            // Contious timestamp in us (no clear time reference)
            struct timespec t;
            clock_gettime(CLOCK_MONOTONIC, &t);
            e.t = 1000000ull*(uint64_t)(t.tv_sec) + (uint64_t)(t.tv_nsec)/1000ull;

            events_buffer.push_back(e);
        }

        mutex.unlock();

        // Wait for 1 s
        usleep(1000 * 1000);
    }
}

void edvs_transmit_app(TcpServer *server)
{
    while (global_stop == 0)
    {
        if (events_buffer.size() > 0)
        {
            mutex.lock();

            // Deliver all read events to connected devices
            Message_EventCollection msg;
            msg.set_events(events_buffer);

            server->clients()->deliver(&msg);
            std::cout << "clients: " << server->clients()->clients_size() << std::endl;

            // After sending delete everything
            events_buffer.clear();

            mutex.unlock();
        }

        usleep(10 * 1000);
    }
}

int robot_movement_control_app(Robot *robot)
{
    while (global_stop == 0)
    {
        // Timeout for client robot control, 500 ms
        if (robot->duration_since_last_cmd_update() > 500)
        {
            static int counter = 0;

            robot->stop();

            if (counter++ % 25 == 0)
            {
                robot->beep();
            }
        }

        // Sleep 0.2 seconds
        usleep(200 * 1000);
    }

    return 0;
}

int main(int /*argc*/, char** /*argv[]*/)
{
    std::cout << "oculus-server v1" << std::endl;

    boost::asio::io_service io_service;
    Robot robot;

    // Setup dispatcher
    auto dispatcher = new Dispatcher();
    dispatcher->addListener(&robot, Message_RobotCommand::type_id);


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

