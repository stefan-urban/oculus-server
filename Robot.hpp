#ifndef ROBOT_H
#define ROBOT_H

#include <vector>

#include "vendor/dispatcher/Dispatcher.hpp"


class Robot : public DispatcherListener
{
public:
    Robot();
    void event(DispatcherEvent event);
    void update_states(std::vector<bool> button_states, std::vector<int> axis_states);
};

#endif // ROBOT_H
