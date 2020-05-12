#ifndef MONSTER_H
#define MONSTER_H

#include "window.hpp"
#include "Caracter.hpp"

typedef enum monsterType {

    Shadow = 0,
    Speedy ,
    Bashful,
    Pokey,

} monsterType;

class Monster : public Caracter
{
private:
    
    monsterType type;
    sf::RectangleShape monster;
    
    

public:

    Monster() = default;

    Monster(monsterType type);

    void display();
    
    bool isInside(int x,int y);

    void  move(Map* map,Pacman pacman);

    Direction changeDirection(Pacman pacman);
};

Monster::Monster(monsterType type)
{   

    this->type = type;
    speed = 1;

    monster.setSize(sf::Vector2f(MONSTER_SIZE, MONSTER_SIZE));

    switch (type)
    {
    case Speedy:

        monster.setFillColor(sf::Color(250, 197, 246));
        x = 14*CELL_SIZE - MONSTER_SIZE/2;
        y = 16*CELL_SIZE + MONSTER_SIZE/2;

        direction = WEST;
    
        break;

    case Pokey:
        monster.setFillColor(sf::Color(247, 187, 20));
        x = 16*CELL_SIZE - MONSTER_SIZE/2;
        y = 16*CELL_SIZE + MONSTER_SIZE/2;
        direction = NORTH;
        break;

    case Bashful:
        monster.setFillColor(sf::Color::Cyan);
        x = 12*CELL_SIZE - MONSTER_SIZE/2;
        y = 16*CELL_SIZE + MONSTER_SIZE/2;
        direction = NORTH;
        break;
    
    case Shadow:
        monster.setFillColor(sf::Color::Red);
        x = 14*CELL_SIZE - MONSTER_SIZE/2;
        y = 13*CELL_SIZE + MONSTER_SIZE/2;
        // direction = EAST;
        nextDirection = WEST;
        break;
    
    default:
        break;
    }
    


    
}


void Monster::move(Map* map,Pacman pacman){

        int xr = x+ MONSTER_SIZE/2;
        int yr = y+ MONSTER_SIZE/2;

        nextDirection = changeDirection(pacman);

        if (  (xr + CELL_SIZE/2) % CELL_SIZE == 0  and nextDirection %2 == 0)
            direction = nextDirection;
        if ( (yr + CELL_SIZE/2) % CELL_SIZE == 0 and nextDirection %2 == 1 )
            direction = nextDirection;
            

        int j = xr / CELL_SIZE;
        int i = yr / CELL_SIZE;


        switch (direction)
        {
        case NORTH:
            if (isInside(x, y - speed) && canMove(map , (yr - speed - CELL_SIZE/2) / CELL_SIZE , j) )
                y -= speed;
            break;

        case SOUTH:
            if (isInside(x, y + speed) && canMove(map , (yr  + CELL_SIZE/2) / CELL_SIZE  , j) )
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

}


void Monster::display(){

    monster.setPosition(x,y);            
    window.draw(monster);

}

bool Monster::isInside(int x,int y){

    if ( x <= 0 or x + MONSTER_SIZE > CELL_SIZE*WIDTH or y <= 0 or y+ MONSTER_SIZE > CELL_SIZE*HEIGHT)
    {
        return false;
    }
    return true;
    
}

Direction Monster::changeDirection(Pacman pacman){


    int xp = pacman.getX();
    int yp = pacman.getY();


    if ( x < xp)
    {
        return EAST;
    }else{
        return WEST;
    }

    if ( y < yp)
    {
        return EAST;
    }else{
        return WEST;
    }
    

}


#endif