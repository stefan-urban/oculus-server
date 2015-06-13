#ifndef TCP_MESSAGE_HPP
#define TCP_MESSAGE_HPP

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <deque>

#include "Message.hpp"


class TcpMessage
{
public:
    enum { header_length = 10 };
    enum { max_body_length = 65536 };

    TcpMessage()
    : body_length_(0)
    {
    }

    const char* data() const
    {
        return data_;
    }

    char* data()
    {
        return data_;
    }

    std::size_t length() const
    {
        return header_length + body_length_;
    }

    const char* body() const
    {
        return data_ + header_length;
    }

    char* body()
    {
        return data_ + header_length;
    }

    std::size_t body_length() const
    {
        return body_length_;
    }

    void body_length(std::size_t new_length)
    {
        body_length_ = new_length;
        if (body_length_ > max_body_length)
            body_length_ = max_body_length;
    }

    void message(Message *msg)
    {
        message_ = msg;
    }

    void encode();
    void decode();
    bool decode_header();
    void encode_header();

private:
    char data_[header_length + max_body_length];
    std::size_t body_length_;
    Message *message_;

};

typedef std::deque<TcpMessage> TcpMessageQueue;


#endif // TCP_MESSAGE_HPP
