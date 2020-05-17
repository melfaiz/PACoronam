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

<<<<<<< HEAD
bool tunnel::is_in_tunnel(double xr, Direction direction){

    if(xr >= 27*CELL_SIZE || xr <= 1*CELL_SIZE)
=======
bool tunnel::is_in_tunnel(double x, Direction direction){

    if(x > 27.5*CELL_SIZE - PACMAN_RADIUS-0.5 || x < 0.5*CELL_SIZE - PACMAN_RADIUS-0.5)
>>>>>>> c111a05056d7f9951e167b225032c0e3038244e9
        return true;

    return false;

}

tunnel::tunnel(){}
