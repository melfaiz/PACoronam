#ifndef MONSTER_H
#define MONSTER_H

#include "Character.hpp"
#include "Pacman.hpp"
#include <vector>
#include <cmath>

typedef enum monsterType {

    Shadow = 0,
    Speedy ,
    Bashful,
    Pokey,

} monsterType;

typedef enum mode {

    chase = 0,
    scatter,
    panic,

} Mode;

class Monster : public Caracter
{
private:
    
    monsterType type;
    sf::RectangleShape monster;
    Mode mode;
    
    

public:

    Monster() = default;

    Monster(monsterType type);

    void display(sf::RenderWindow &window);
    
    bool isInside(int x,int y);

    void  move(Map* map,Pacman pacman);

    Direction changeDirection(Map *map,Pacman pacman);

    Direction chasePoint(Map* map,float xp,float yp);

    
};



#endif