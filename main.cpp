#include <iostream>
#include <deque>
#include <set>
#include <list>
#include <random>
#include <time.h>
#include <boost/asio.hpp>
#include <boost/thread.hpp>

#include "Robot.hpp"
#include "TcpServer.hpp"
#include "TcpMessage.hpp"
#include "EdvsEventsCollection.hpp"
#include "Message_EventCollection.hpp"
#include "vendor/edvstools/Edvs/EventStream.hpp"
#include "vendor/dispatcher/Dispatcher.hpp"


#define DEBUG 1

void edvs_app(TcpServer *server)
{
    std::vector<std::string> p_vuri = {"127.0.0.1:7001 127.0.0.1:7002"};
    EdvsEventsCollection events_buffer;

#if DEBUG == 0
    auto stream = Edvs::OpenEventStream(p_vuri);

    if (stream->is_open())
    {
        //std::cout << "eDVS stream open" << std::endl;
    }
    else
    {
        std::cout << "eDVS stream NOT opened" << std::endl;
        return;
    }
#endif

    while (1)
    {
#if DEBUG == 0
        auto events = stream->read();

        for(const Edvs::Event& e : events) {
            events_buffer.push_back(e);
        }
#else
        EdvsEventsCollection events;

        for (int i = 0; i < 10; i++)
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
#endif

        if (events_buffer.size() > 0)
        {
            // Deliver all read events to connected devices
            Message_EventCollection msg;
            msg.set_events(events_buffer);

            // Wrap and send
            TcpMessage tcpMsg;
            tcpMsg.message(&msg);

            server->clients()->deliver(tcpMsg);
#if DEBUG == 0
            std::cout << " --------------------------------------------------------- ";
#endif
            std::cout << "clients: " << server->clients()->clients_size() << std::endl;
        }

        //delete(&msg);

        // After sending delete everything
        events_buffer.clear();

#if DEBUG == 0
        // Wait for 5 ms
        usleep(5 * 1000);
#else
        // Wait for 1 s
        usleep(1000 * 1000);
#endif
    }
}

int robot_movement_control_app(Robot *robot)
{


    return 0;
}

int main(int argc, char* argv[])
{
    std::cout << "oculus-server v1" << std::endl;

    // Create io service
    boost::asio::io_service io_service;

    // Robot movement control
    Robot robot;

    // Setup dispatcher
    auto dispatcher = new Dispatcher();

    dispatcher->addListener(&robot);

    // Setup TCP server
    boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::tcp::v4(), 4000);

    TcpServer server(io_service, endpoint, dispatcher);

    // Start threads
    boost::thread eda(edvs_app, &server);
    boost::thread rca(robot_movement_control_app, &robot);

    io_service.run();

    eda.join();
    rca.join();

    return 0;
}
