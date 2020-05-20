#ifndef CORONA_H
#define CORONA_H

#include "constants.hpp"
#include "Pacman.hpp"
#include "shadow.hpp"
#include "speedy.hpp"
#include "pokey.hpp"
#include "bashful.hpp"

#include <random>

class corona{

public:

    corona();
    void update(Pacman* pacman, bashful* inky, pokey* clyde, speedy* pinky, shadow* blinky);
    void restart();

private:

    int sickness_counter;
    int which_monster;
    int time_virus;
    int time_random;
    bool set_v;
    int blinky_time;
    int pinky_time;
    int inky_time;
    int clyde_time;
    int pacman_time;

};

#endif // CORONA_H

