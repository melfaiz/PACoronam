#include "tunnel.hpp"



double tunnel::in_tunnel(double x, double speed, Direction direction){

    if(direction == EAST){
        x += speed;
        if(x >= 29*CELL_SIZE)
            x = -2*CELL_SIZE;
    }

    if(direction == WEST){
        x -= speed;
        if(x <= -2*CELL_SIZE)
            x = 29*CELL_SIZE;
    }

    return x;

}

bool tunnel::is_in_tunnel(double x, Direction direction){

    if(x > 27.5*CELL_SIZE - PACMAN_RADIUS-0.5 || x < 0.5*CELL_SIZE - PACMAN_RADIUS-0.5)
        return true;

    return false;

}

tunnel::tunnel(){}
