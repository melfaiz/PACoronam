#ifndef CARACTER_H
#define CARACTER_H

typedef enum direction {
	NORTH = 0,
	EAST,  // 1
	SOUTH, // 2
	WEST,   // 3
	INITIAL
} Direction;

class Caracter
{
protected:
    int x;
    int y;
    Direction direction = INITIAL;
    Direction nextDirection;
    double speed;



public:

    Caracter(){
        x = 0;
        y = 0;
    }

};




#endif
