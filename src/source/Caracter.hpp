#ifndef CARACTER_H
#define CARACTER_H

typedef enum direction {
	NORTH = 0,
	EAST,  // 1
	SOUTH, // 2
	WEST,   // 3
	// INITIAL
} Direction;

class Caracter
{
protected:
    float x;
    float y;
    Direction direction = WEST;
    Direction nextDirection;
    double speed;

    bool canMove(Map* map,int i,int j);

    

public:



};

bool Caracter::canMove(Map* map,int i,int j){

    if ( map->getCellType(i, j) == EMPTY or map->getCellType(i, j) == TREAT or map->getCellType(i, j) == PILL)
    {
        return true;
    }
    return false;
}


#endif
