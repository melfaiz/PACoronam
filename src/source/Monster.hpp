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
    

public:

    Monster(){

        
            
    }

    Monster(monsterType type);

    void display();
    
    
};

Monster::Monster(monsterType type)
{   

    this->type = type;
    caracter.setRadius(MONSTER_SIZE);

    switch (type)
    {
    case Shadow:
        caracter.setFillColor(sf::Color(250, 197, 246));
        x = 150;
        y = 150;
    
        break;
    case Speedy:
        caracter.setFillColor(sf::Color(247, 187, 20));
        x = 150;
        y = 180;
        break;
    
    
    default:
        break;
    }
    


    
}

void Monster::display(){

    caracter.setPosition(x,y);            
    window.draw(caracter);

}



#endif