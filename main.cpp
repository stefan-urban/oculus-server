#include <iostream>
#include <deque>
#include <set>
#include <list>
#include <boost/asio.hpp>
#include <boost/thread.hpp>

#include "TcpServer.hpp"
#include "TcpMessage.hpp"
#include "EdvsEventsCollection.hpp"
#include "Message_EventCollection.hpp"
#include "vendor/edvstools/Edvs/EventStream.hpp"


void edvs_thread(TcpServer *server)
{
    std::vector<std::string> p_vuri = {"127.0.0.1:7001 127.0.0.1:7002"};
    EdvsEventsCollection events_buffer;

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

    while (1)
    {
        auto events = stream->read();

        for(const Edvs::Event& e : events) {

            events_buffer.push_back(e);
        }

        if (events_buffer.size() > 0)
        {
            // Deliver all read events to connected devices
            Message_EventCollection msg;
            msg.set_events(events_buffer);

            // Wrap and send
            TcpMessage tcpMsg;
            tcpMsg.message(&msg);

            server->clients()->deliver(tcpMsg);
            std::cout << " --------------------------------------------------------- clients: " << server->clients()->clients_size() << std::endl;
        }

        //delete(&msg);

        // After sending delete everything
        events_buffer.clear();

        // Wait for 1 s
        usleep(100 * 1000);
    }
}

int main(int argc, char* argv[])
{
    std::cout << "oculus-server v1" << std::endl;

    try
    {
        boost::asio::io_service io_service;

        boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::tcp::v4(), 4000);
        TcpServer server(io_service, endpoint);

        boost::thread et(edvs_thread, &server);

        io_service.run();
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}
