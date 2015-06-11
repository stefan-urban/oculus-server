#include "TcpMessage.hpp"

#include <cstdio>

bool TcpMessage::decode_header()
{
    // Header contains number of bytes in body
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
    std::sprintf(header, "%6d", static_cast<int>(body_length_));
    std::memcpy(data_, header, header_length);
}
