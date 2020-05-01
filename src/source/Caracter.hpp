#ifndef CARACTER_H
#define CARACTER_H

typedef enum direction {
	NORTH = 0,
	EAST,  // 1
	SOUTH, // 2
	WEST   // 3
} Direction;

class Caracter
{
protected:
    int x;
    int y;
    Direction direction;
    int speed;

    sf::CircleShape caracter;

public:
    Caracter(){
        x = 0;
        y = 0;
        speed = 1;
        direction = SOUTH;
    }

    void move();

    void changeDirection(Direction direction);



};

void Caracter::move(){

    switch (direction)
    {
    case NORTH:
        y -= speed;
        break;

    case SOUTH:
        y += speed;
        break;

    case EAST:
        x -= speed;
        break;

    case WEST:
        x += speed;

    default:
        break;
    }

}


void Caracter::changeDirection(Direction direction){

    this->direction = direction;
}


#endif
