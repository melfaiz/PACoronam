#ifndef CORONA_H
#define CORONA_H

#include "constants.hpp"
#include <random>

class corona{

public:

    corona();
    corona_state state(bool viral);
    void restart_system();
    bool is_sick();

private:

    int sickness_counter;

};

#endif // CORONA_H
