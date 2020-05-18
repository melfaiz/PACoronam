#ifndef POKEY_H
#define POKEY_H

#include "Character.hpp"
#include "Pacman.hpp"

#include <vector>
#include<cmath>

class pokey: public Caracter
{
public :

    pokey();
    void restart();
    void move(Map *map, Pacman pacman);
    void display(sf::RenderWindow &window);

    float getX();
    float getY();
    void is_dead();

private:

    bool in_tunnel;
    sf::RectangleShape pokey_draw;
    Mode mode;
    float chaseX;
    float chaseY;
    const float speed_ref = 1;

    float getDistanceIndices(int ia, int ja, int ib, int jb);
    bool canMove(Map* map,int i, int j);
    Direction start(Map *map);
    Direction chasePoint(Map *map, float xp, float yp);
    void changeDirection(Map *map, Pacman pacman);
    Direction randomDirection(Map* map);
    void change_mode(bool pills, bool restart_);

};

#endif // POKEY
