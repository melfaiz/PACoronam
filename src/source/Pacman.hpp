#ifndef PACMAN_H
#define PACMAN_H

#include "window.hpp"
#include "Caracter.hpp"
#include "Map.hpp"

#include <iostream>

class Pacman : public Caracter
{
private:
    bool infected;
    int r;
    int score;
    sf::CircleShape pacman;
    bool middle();
    bool u_move();
    bool eat(Map* map, int i, int j);
    bool angle(Map* map, int i, int j);
    bool turning = false;
    void turn(int xr, int yr);
    Direction final_dir;
    int xr = x + PACMAN_RADIUS;
    int yr = y + PACMAN_RADIUS;

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
    point.setRadius(1);
    point.setPosition(x+PACMAN_RADIUS-1,y+PACMAN_RADIUS-1);
    point.setFillColor(sf::Color::Magenta);
    window.draw(point);
}



//Return true if we are in the first half of a cell
bool Pacman::middle(){

    switch (direction)
        {
        case NORTH:
            if ((CELL_SIZE/2) <= (yr % CELL_SIZE))
                return true;
            break;

        case SOUTH:
            if ((yr % CELL_SIZE ) <= CELL_SIZE/2)
                return true;
            break;

        case EAST:
            if ((xr % CELL_SIZE) <= CELL_SIZE/2)
                return true;
            break;

        case WEST:
            if ((CELL_SIZE/2) <= (xr % CELL_SIZE))
                return true;
            break;

        default:
            break;
        }

        return false;
}

//Detect if the next move is a U move :
bool Pacman::u_move(){

    if(direction == NORTH || direction == SOUTH){
        if(nextDirection == NORTH || nextDirection == SOUTH)
            return true;
    }

    if(direction == EAST || direction == WEST){
        if(nextDirection == EAST || nextDirection == WEST)
            return true;
    }

    return false;
}

//Detect if Pac-man eat :
bool Pacman::eat(Map* map, int i, int j){

    //if we eat :
    if (map->getCellType(i, j) == TREAT)
    {
        score += 10;
        map->setCellType(i, j, EMPTY);
        return true;
    }
    if (map->getCellType(i, j) == PILL)
    {
        score += 100;
        map->setCellType(i, j, EMPTY);
        return true;
    }

    return false;
}

//Detect if we want to turn, and if it is possible :
bool Pacman::angle(Map* map,int i, int j){

    if(direction == NORTH || direction == SOUTH){
        if(nextDirection == EAST && canMove(map,i,j+1))
            return true;
        if(nextDirection == WEST && canMove(map,i,j-1))
            return true;
    }

    if(direction == EAST || direction == WEST){
        if(nextDirection == NORTH && canMove(map,i-1,j))
            return true;
        if(nextDirection == SOUTH && canMove(map,i+1,j))
            return true;
    }

    return false;

    //if (  (xr + CELL_SIZE/2) % CELL_SIZE == 0  and nextDirection %2 == 0)
        //        direction = nextDirection;
    //if ( (yr + CELL_SIZE/2) % CELL_SIZE == 0 and nextDirection %2 == 1 )
      //          direction = nextDirection;

}

void Pacman::turn(int xr, int yr){

    //If the turn is finish :
    if((final_dir == NORTH || final_dir == SOUTH) && (xr%(CELL_SIZE/2)) == 0 && (xr%(CELL_SIZE)) != 0){
        turning = false;
        direction = final_dir;
    }

    if((final_dir == EAST || final_dir == WEST) && (yr%(CELL_SIZE/2)) == 0 && (yr%(CELL_SIZE)) != 0){
        turning = false;
        direction = final_dir;
    }

    switch(direction){

    //If previously we go to the North :
    case NORTH:
        //To EAst :
        if(final_dir == EAST){
            x += speed;
            y -= speed;
        }

        //To West
        if(final_dir == WEST){
            x -= speed;
            y -= speed;
        }
        break;

    //If previously we go to the South :
    case SOUTH:
        if(final_dir == EAST){
            x += speed;
            y += speed;
        }

        if(final_dir == WEST){
            x -= speed;
            y += speed;
        }
        break;
    case EAST:
        if(final_dir == NORTH){
            x += speed;
            y -= speed;
        }

        if(final_dir == SOUTH){
            x += speed;
            y += speed;
        }
        break;
    case WEST:
        if(final_dir == NORTH){
            x -= speed;
            y -= speed;
        }

        if(final_dir == SOUTH){
            x -= speed;
            y += speed;
        }
        break;
    default:
        break;
    }

}

//Apply the move on the Pac-man :
void Pacman::move(Map* map){

        // We compute the center :
        xr = x+PACMAN_RADIUS;
        yr = y+PACMAN_RADIUS;

        // We compute the current cell :
        int j = xr / CELL_SIZE;
        int i = yr / CELL_SIZE;

        //If this is the first move of the game :
        if(direction == INITIAL){
            if(nextDirection == EAST){
                x -= speed;
                direction = nextDirection;
            }
            if(nextDirection == WEST){
                x += speed;
                direction = nextDirection;
            }
        }



        if(turning)
            turn(xr,yr);

        else{

            //If we don't eat, we are in the first middle of the cell, and we want to turn :
            if(!eat(map,i ,j) && middle() && angle(map,i,j)){
                final_dir = nextDirection;
                turning = true;
                turn(xr,yr);

            }

            //If this is a // move or the same move :
            else{

                if(u_move())
                    direction = nextDirection;

                switch (direction)
                {
                case NORTH:
                    if (canMove(map, (yr - speed - CELL_SIZE/2) / CELL_SIZE  ,j) )
                        y -= speed;
                    break;

                case SOUTH:
                    if (canMove(map, (yr  + CELL_SIZE/2) / CELL_SIZE  ,j) )
                        y += speed;
                    break;

                case WEST:
                    if (canMove(map, i  ,(xr - speed - CELL_SIZE/2) / CELL_SIZE) )
                        x -= speed;
                    break;

                case EAST:
                    if (canMove(map, i  ,(xr  + CELL_SIZE/2) / CELL_SIZE) )
                        x += speed;

                default:
                    break;
                }
            }

        }

}

void Pacman::changeDirection(Direction dir){
    this->nextDirection = dir;

}


#endif
