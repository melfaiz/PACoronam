
#include "../include/corona.hpp"

#include <iostream>
#include <time.h>

void corona::restart(){

    sickness_counter = 0;

    srand(time(NULL));
    which_monster = rand()%3;

    time_virus = 0;
    time_random = LATEST_VIRUS;
    set_v = false;

    blinky_time = 0;
    pinky_time = 0;
    inky_time = 0;
    clyde_time = 0;
    pacman_time = 0;

}

void corona::update(Pacman* pacman, bashful* inky, pokey* clyde, speedy* pinky, shadow* blinky){

    //std::cout << time_virus << " " << time_random << "\n";
    //std::cout << which_monster << "\n";

    if(!set_v && time_virus >= time_random){

        switch(which_monster){
        case 0:
            blinky->state = incubation;
            break;
        case 1:
            clyde->state = incubation;
            break;
        case 2:
            inky->state = incubation;
            break;
        case 3:
            pinky->state = incubation;
            break;
        }

        set_v = true;
    }

    if(pacman->state == incubation || pacman->state == sick){
        if(pacman_time >= 30*GAME_FPS)
            pacman->state = imunate;
        if(pacman_time >= 20*GAME_FPS && pacman_time < 30*GAME_FPS)
            pacman->state = sick;
        pacman_time++;
    }

    if(blinky->state == incubation || blinky->state == sick){

        if(blinky_time >= 30*GAME_FPS){
            blinky->state = imunate;
            blinky_time = 0;
        }
        if(blinky_time >= 20*GAME_FPS && blinky_time < 30*GAME_FPS)
            blinky->state = sick;

        if(blinky->mode == dead){
            blinky->state = healthy;
            blinky_time = 0;
        }

        blinky_time++;
    }

    if(inky->state == incubation || inky->state == sick){
        if(inky_time >= 30*GAME_FPS){
            inky->state = imunate;
            inky_time = 0;
        }
        if(inky_time >= 20*GAME_FPS && inky_time < 30*GAME_FPS)
            inky->state = sick;

        if(inky->mode == dead){
            inky->state = healthy;
            inky_time = 0;
        }
        inky_time++;
    }

    if(clyde->state == incubation || clyde->state == sick){
        if(clyde_time >= 30*GAME_FPS){
            clyde->state = imunate;
            clyde_time = 0;
        }
        if(clyde_time >= 20*GAME_FPS && clyde_time < 30*GAME_FPS)
            clyde->state = sick;

        if(clyde->mode == dead){
            clyde->state = healthy;
            clyde_time = 0;
        }

        clyde_time++;
    }

    if(pinky->state == incubation || pinky->state == sick){
        if(pinky_time >= 30*GAME_FPS){
            pinky->state = imunate;
            pinky_time = 0;
        }
        if(pinky_time >= 20*GAME_FPS && pinky_time < 30*GAME_FPS)
            pinky->state = sick;

        if(pinky->mode == dead){
            pinky->state = healthy;
            pinky_time = 0;
        }

        pinky_time++;
    }


    //Counter to deploy the virus
    time_virus++;
}

//Constructor :
corona::corona(){

    sickness_counter = 0;

    srand(time(NULL));
    which_monster = rand()%3;

    time_virus = 0;
    time_random = LATEST_VIRUS;
    set_v = false;

    blinky_time = 0;
    pinky_time = 0;
    inky_time = 0;
    clyde_time = 0;
    pacman_time = 0;

}
