#include "SerialCommunication.hpp"

#include <fstream>


SerialCommunication::SerialCommunication(std::string port)
{
    open(port);
}

bool SerialCommunication::open(std::string port)
{
    port_ = port;

    fd_ = ::open(port.c_str(), O_RDWR);

    if (fd_ < 0)
    {
        return false;
    }

    return true;
}

ssize_t SerialCommunication::read(char *buffer, ssize_t n)
{
    return ::read(fd_, (void*) buffer, n);
}

ssize_t SerialCommunication::write(const char *buffer, ssize_t n)
{
    return ::write(fd_, (void*) buffer, n);
}

bool SerialCommunication::close()
{
    ::close(fd_);

    return true;
}
