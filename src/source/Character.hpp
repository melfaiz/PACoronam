#ifndef CARACTER_H
#define CARACTER_H

#include "Map.hpp"
#include "constants.hpp"


class Caracter{

protected:

    //Coordinates :
    float x;
    float y;

    Direction direction = INITIAL;
    Direction nextDirection;

    float speed;

    bool canMove(Map* map,int i,int j);

public:
    void changeDirection(Direction direction);

};

#endif

