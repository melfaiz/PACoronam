#include "../include/tunnel.hpp"



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

bool tunnel::is_in_tunnel(double xr, Direction direction){

    if(xr >= 27*CELL_SIZE || xr <= 1*CELL_SIZE)
        return true;

    return false;

}

tunnel::tunnel(){}
