#ifndef SERIALCOMMUNICATION_HPP
#define SERIALCOMMUNICATION_HPP

#include <string>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>


class SerialCommunication
{
public:
    SerialCommunication()
    {
    }

    SerialCommunication(std::string port);


    bool open(std::string port);
    ssize_t read(char *buffer, ssize_t n);
    ssize_t write(const char *buffer, ssize_t n);

    bool close();


private:
    std::string port_;
    int fd_ = -1;
};

#endif // SERIALCOMMUNICATION_HPP
