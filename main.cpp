
#include <iostream>
#include <deque>
#include <set>
#include <list>
#include <boost/asio.hpp>

#include "TcpServer.hpp"

int main(int argc, char* argv[])
{
    std::cout << "oculus-server v1" << std::endl;

    try
    {
        if (argc < 2)
        {
            std::cerr << "Usage: oculus-server <port> [<port> ...]\n";
            return 1;
        }

        boost::asio::io_service io_service;

        std::list<TcpServer> servers;
        for (int i = 1; i < argc; ++i)
        {
            boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::tcp::v4(), std::atoi(argv[i]));
            servers.emplace_back(io_service, endpoint);
        }

        io_service.run();
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}
