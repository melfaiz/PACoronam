#ifndef MONSTER_H
#define MONSTER_H


#include "Character.hpp"
#include "Pacman.hpp"

#include <vector>
#include<cmath>

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
    on

} Mode;

class Monster : public Caracter
{
private:

    monsterType type;
    sf::RectangleShape monster;
    Mode mode;
    float chaseX;
    float chaseY;
    bool in_tunnel;

    bool canMove(Map *map, int i, int j);
    bool isInside(int x, int y);
    float getDistanceIndices(int ia, int ja, int ib, int jb);
    Direction randomDirection(Map* map);
    void changeDirection(Map *map, Pacman pacman);
    Direction chasePoint(Map *map, float xp, float yp);
    void change_mode();


public:

    Monster(monsterType type);
    void display(sf::RenderWindow &window);
    void move(Map *map, Pacman pacman);
    Direction start(Map *map);
    float getX();
    float getY();

};

#endif
