#ifndef PACMAN_H
#define PACMAN_H

#include "window.hpp"
#include "Caracter.hpp"
#include "Map.hpp"

class Pacman : public Caracter
{
private:
    bool infected;
    int r;
    int score;
    sf::CircleShape pacman;

public:
    Pacman(){

        infected = false;
        x = 14*CELL_SIZE - PACMAN_RADIUS;
        y = 26.5*CELL_SIZE - PACMAN_RADIUS;
        speed = 2;
        score = 0;

        pacman.setRadius(PACMAN_RADIUS);
        pacman.setFillColor(sf::Color(255,238,0));
        
    }

    void display();
    bool isInside(int x,int y);
    void move(Map* map);
    void changeDirection(Direction direction);
    int getScore(){
        return score;
    }

    int getX(){
        return x;
    }
    int getY(){
        return x;
    }

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




void Pacman::move(Map* map){

        int xr = x+PACMAN_RADIUS;
        int yr = y+PACMAN_RADIUS;

        if (  (xr + CELL_SIZE/2) % CELL_SIZE == 0  and nextDirection %2 == 0)
            direction = nextDirection;
        if ( (yr + CELL_SIZE/2) % CELL_SIZE == 0 and nextDirection %2 == 1 )
            direction = nextDirection;

        int j = ( x+ PACMAN_RADIUS) / CELL_SIZE;
        int i = ( y+ PACMAN_RADIUS) / CELL_SIZE;


        switch (direction)
        {
        case NORTH:
            if (isInside(x, y - speed) && canMove(map, (yr - speed - CELL_SIZE/2) / CELL_SIZE  ,j) )
                y -= speed;
            break;

        case SOUTH:
            if (isInside(x, y + speed) && canMove(map, (yr  + CELL_SIZE/2) / CELL_SIZE  ,j) )
                y += speed;
            break;

        case EAST:
            if (isInside(x - speed, y) && canMove(map, i  ,(xr - speed - CELL_SIZE/2) / CELL_SIZE) )
                x -= speed;
            break;

        case WEST:
            if (isInside(x + speed, y) && canMove(map, i  ,(xr  + CELL_SIZE/2) / CELL_SIZE) )
                x += speed;

        default:
            break;
        }

        if (map->getCellType(i, j) == TREAT)
        {
            score += 10;
            map->setCellType(i, j, EMPTY);
        }
        if (map->getCellType(i, j) == PILL)
        {
            score += 100;
            map->setCellType(i, j, EMPTY);
        }
}

void Pacman::changeDirection(Direction dir){

    this->nextDirection = dir;

}


#endif