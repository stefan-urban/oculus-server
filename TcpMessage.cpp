#include "TcpMessage.hpp"


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

    // Get type
    char type_str[type_length + 1] = "";
    std::strncat(type_str, data_ + header_length, type_length);
    type = std::atoi(type_str);

    return true;
}

void TcpMessage::encode_header()
{
    char header[header_length + type_length + 1] = "";
    std::sprintf(header, "%4d%2d", static_cast<int>(body_length_), static_cast<int>(type));
    std::memcpy(data_, header, header_length + type_length);
}
