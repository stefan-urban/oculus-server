#ifndef TCP_MESSAGE_HPP
#define TCP_MESSAGE_HPP

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <deque>

class TcpMessage
{
public:
    enum { header_length = 6 };
    enum { type_length = 2 };
    enum { max_body_length = 65536 };

    TcpMessage()
    : body_length_(0),
      type_(0)
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
        return header_length + type_length + body_length_;
    }

    const char* body() const
    {
        return data_ + header_length + type_length;
    }

    char* body()
    {
        return data_ + header_length + type_length;
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

    int type() const
    {
        return type_;
    }

    bool decode_header();
    void encode_header();

private:
    char data_[header_length + max_body_length];
    std::size_t body_length_;

protected:
    int type_;
};

typedef std::deque<TcpMessage> TcpMessageQueue;


#endif // TCP_MESSAGE_HPP
