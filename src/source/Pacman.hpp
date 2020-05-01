#ifndef PACMAN_H
#define PACMAN_H

#include "window.hpp"
#include "Caracter.hpp"

class Pacman : public Caracter
{
private:
    bool infected;
    int r;
    sf::CircleShape pacman;

public:
    Pacman(){

        r = PACMAN_RADIUS;
        infected = false;
        x = 5.5*CELL_SIZE - PACMAN_RADIUS;
        y = 5.5*CELL_SIZE - PACMAN_RADIUS;
        speed = 1;

        pacman.setRadius(PACMAN_RADIUS);
        pacman.setFillColor(sf::Color(255,238,0));
        
    }

    void display();
    bool isInside(int x,int y);
    void move();
    void changeDirection(Direction direction);

};


void Pacman::display(){    

    pacman.setPosition(x,y);
    window.draw(pacman);

    sf::CircleShape point;
    point.setRadius(3);
    point.setPosition(x+r-3,y+r-3);
    point.setFillColor(sf::Color::Magenta);
    window.draw(point);


    

}

bool Pacman::isInside(int x,int y){

    if ( x <= 0 or x + 2* r > CELL_SIZE*WIDTH or y <= 0 or y+ 2*r > CELL_SIZE*HEIGHT)
    {
        return false;
    }
    return true;
    
}


void Pacman::move(){


        if (  (x+r) % (CELL_SIZE/2) == 0  and nextDirection %2 == 0 )
            direction = nextDirection;
        if ( (y+r) % (CELL_SIZE/2) == 0 and nextDirection %2 == 1 )
            direction = nextDirection;
        

        switch (direction)
        {
        case NORTH:
            if(isInside(x,y-speed))
                y -= speed;

            break;

        case SOUTH:
            if(isInside(x,y+speed))
                y += speed;
            break;

        case EAST:
            if(isInside(x-speed,y))
                x -= speed;
            break;

        case WEST:
            if(isInside(x+speed,y))
                x += speed;

        default:
            break;
        }
  

}

void Pacman::changeDirection(Direction dir){



    
    this->nextDirection = dir;
}


#endif