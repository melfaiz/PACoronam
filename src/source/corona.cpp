#include "corona.hpp"

#include <iostream>
#include <time.h>

//New life of the mob :
void corona::restart_system(){

    sickness_counter = 0;

}


//God will decide if we are infected:
bool corona::is_sick(){

    srand(time(NULL));
    static int it_is_time = 50;//(rand()%60*GAME_FPS+0);
    static int god_counter = 0;
    if(god_counter++ >= it_is_time){
        it_is_time = rand() % 60*GAME_FPS;
        return true;
    }
    return false;

}

//Return the current state of the health of a character
corona_state corona::state(bool viral){

    if(sickness_counter > ((20+10)*GAME_FPS)){
        sickness_counter++;
        return imunate;
    }

    else if(sickness_counter > (20*GAME_FPS)){
        sickness_counter++;
        return sick;
    }

    else{
        if(viral){
            sickness_counter++;
            return incubation;
        }

        return healthy;
    }

}





//Constructor :
corona::corona(){

    sickness_counter = 0;

}
