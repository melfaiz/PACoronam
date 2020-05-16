#ifndef MONSTER_H
#define MONSTER_H

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
    on,

} Mode;

class Monster : public Caracter
{
private:
    
    monsterType type;
    sf::RectangleShape monster;
    Mode mode;

    float chaseX;
    float chaseY;
    
    

public:

    Monster() = default;

    Monster(monsterType type);

    void display(sf::RenderWindow &window);
    
    bool isInside(int x,int y);

    void  move(Map* map,Pacman pacman);

    void changeDirection(Map *map,Pacman pacman);

    Direction chasePoint(Map* map,float xp,float yp);
    Direction start(Map* map);

    bool canMove(Map* map,int i,int j);

    
};



#endif