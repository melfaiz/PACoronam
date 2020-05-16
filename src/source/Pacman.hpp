#ifndef PACMAN_H
#define PACMAN_H

#include "Character.hpp"
#include "Map.hpp"
#include "tunnel.hpp"

#include <iostream>

class Pacman : public Caracter
{
private:

    sf::CircleShape pacman;

    bool infected;
    bool invincible;
    int score;
    bool turning;
    bool in_tunnel;
    Direction final_dir;

    //initial parameters :
    const double speed_ref = 1;
    const double x_i = 14*CELL_SIZE - PACMAN_RADIUS-0.5;
    const double y_i = y = 26.5*CELL_SIZE - PACMAN_RADIUS;

    int r; // ?


    bool middle(int xy, int yr);
    bool u_move();
    bool eat(Map* map, int i, int j);
    bool angle(Map* map, int i, int j);
    void turn(int xr, int yr);
    void speed_modif(char s);


public:

    Pacman();
    void display(sf::RenderWindow &window);

    int getScore();

    Direction getDirection(){
        return direction;
    }
    double getX();
    double getY();

    void move(Map* map);
    void changeDirection(Direction direction);


};

#endif
