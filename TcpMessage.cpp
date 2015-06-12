#include "TcpMessage.hpp"

#include <cstdio>
#include <sstream>


bool TcpMessage::decode_header()
{
    unsigned char buffer = 0;
    body_length_ = 0;

    for (int i = 0; i < header_length; i++)
    {
        buffer = data_[i] << (i * 8);
        body_length_ += buffer;
    }

    if (body_length_ > max_body_length)
    {
        body_length_ = 0;
        return false;
    }

    return true;
}

void TcpMessage::encode_header()
{
    // todo
    for (int i = 0; i < header_length; i++)
    {
        data_[i] = (body_length_ >> (i * 8)) & 0xFF;
    }
}

void TcpMessage::encode()
{
    std::string body_buffer = message_->serialize();

    // Copy it into data
    body_length_ = body_buffer.size();
    std::memcpy(body(), body_buffer.c_str(), body_length_);

    // And create header
    encode_header();
}


void TcpMessage::decode()
{
    // Obtain body_size_
    decode_header();


}


/*
 *
  text_iarchive ia{ss};
  bird penguin;
  ia >> penguin;
  std::cout << penguin.legs() << '\n';
  std::cout << std::boolalpha << penguin.can_fly() << '\n';
*/
