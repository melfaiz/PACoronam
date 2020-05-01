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
    
    bool isInside();
};

Monster::Monster(monsterType type)
{   

    this->type = type;
    speed = 2;

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
        direction = NORTH;
        break;
    
    default:
        break;
    }
    


    
}

void Monster::display(){

    monster.setPosition(x,y);            
    window.draw(monster);

}

bool Monster::isInside(){
    return true;
}


#endif