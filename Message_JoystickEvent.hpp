#ifndef MESSAGE_JOYSTICKEVENT_HPP
#define MESSAGE_JOYSTICKEVENT_HPP

#include <vector>
#include "Message.hpp"

class Message_JoystickEvent : public Message
{
public:
    enum { type_id = 21 };

    enum { ButtonPressed = 0};
    enum { ButtonReleased = 0};

    Message_JoystickEvent(int button, int state)
        : button_(button)
        , state_(state)
    {
    }

    Message_JoystickEvent()
    {
    }

    unsigned char get_type()
    {
        return (unsigned char) type_id;
    }

    std::vector<unsigned char> serialize();
    void unserialize(std::vector<unsigned char> const *data);

private:
    int button_;
    int state_;
};

#endif // MESSAGE_JOYSTICKEVENT_HPP
