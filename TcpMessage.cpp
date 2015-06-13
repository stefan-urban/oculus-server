#include "TcpMessage.hpp"

#include <cstdio>
#include <sstream>


bool TcpMessage::decode_header()
{
    char header[header_length + 1] = "";
    std::strncat(header, data_, header_length);
    body_length_ = std::atoi(header);

    if (body_length_ > max_body_length)
    {
        body_length_ = 0;
        return false;
    }

    return true;
}

void TcpMessage::encode_header()
{
    char header[header_length + 1] = "";
    std::sprintf(header, "%10d", static_cast<int>(body_length_));
    std::memcpy(data_, header, header_length);
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
