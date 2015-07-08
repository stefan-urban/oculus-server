#include "SerialCommunication.hpp"

#include <fstream>
#include <termios.h>
#include <stdio.h>
#include <fcntl.h>


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

    // set baud rates and other options
    struct termios settings;
    if(tcgetattr(fd_, &settings) != 0) {
        printf("edvs_serial_open: tcgetattr error\n");
        return false;
    }
    if(cfsetispeed(&settings, B4000000) != 0) {
        printf("edvs_serial_open: cfsetispeed error\n");
        return false;
    }
    if(cfsetospeed(&settings, B4000000)) {
        printf("edvs_serial_open: cfsetospeed error\n");
        return false;
    }
    settings.c_cflag = (settings.c_cflag & ~CSIZE) | CS8; // 8 bits
    settings.c_cflag |= CLOCAL | CREAD;
    settings.c_cflag |= CRTSCTS; // use hardware handshaking
    settings.c_iflag = IGNBRK;
    settings.c_oflag = 0;
    settings.c_lflag = 0;
    settings.c_cc[VMIN] = 1; // minimum number of characters to receive before satisfying the read.
    settings.c_cc[VTIME] = 5; // time between characters before satisfying the read.
    // write modified record of parameters to port
    if(tcsetattr(fd_, TCSANOW, &settings) != 0) {
        printf("edvs_serial_open: tcsetattr error\n");
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
