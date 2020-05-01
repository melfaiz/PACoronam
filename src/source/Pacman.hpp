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

        infected = false;
        x = 14*CELL_SIZE - PACMAN_RADIUS;
        y = 26.5*CELL_SIZE - PACMAN_RADIUS;
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
    point.setPosition(x+PACMAN_RADIUS-3,y+PACMAN_RADIUS-3);
    point.setFillColor(sf::Color::Magenta);
    window.draw(point);


    

}

bool Pacman::isInside(int x,int y){

    if ( x <= 0 or x + 2* PACMAN_RADIUS > CELL_SIZE*WIDTH or y <= 0 or y+ 2*PACMAN_RADIUS > CELL_SIZE*HEIGHT)
    {
        return false;
    }
    return true;
    
}


void Pacman::move(){


        if (  (x+PACMAN_RADIUS) % (CELL_SIZE/2) == 0  and nextDirection %2 == 0 )
            direction = nextDirection;
        if ( (y+PACMAN_RADIUS) % (CELL_SIZE/2) == 0 and nextDirection %2 == 1 )
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