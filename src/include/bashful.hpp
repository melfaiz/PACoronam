#ifndef BASHFUL_H
#define BASHFUL_H

#include "Character.hpp"
#include "Pacman.hpp"

#include <vector>
#include<cmath>

class bashful: public Caracter
{
public :

    corona_state state;
    Mode mode;

    bashful();
    void restart();
    void move(Map *map, Pacman pacman);
    void display(sf::RenderWindow &window);

    float getX();
    float getY();
    void is_dead();


private:

    bool in_tunnel;
    sf::RectangleShape bashful_draw;
    float chaseX;
    float chaseY;
    bool is_home;

    float getDistanceIndices(int ia, int ja, int ib, int jb);
    bool canMove(Map* map,int i, int j);
    Direction start(Map *map);
    Direction chasePoint(Map *map, float xp, float yp);
    void changeDirection(Map *map, Pacman pacman);
    Direction randomDirection(Map* map);
    void change_mode(bool pills, bool restart_);
    void go_home();

};

#endif // BASHFUL
