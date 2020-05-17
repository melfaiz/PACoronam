#ifndef PACMAN_H
#define PACMAN_H

#include "Character.hpp"
#include "Map.hpp"
#include "tunnel.hpp"
#include "corona.hpp"

#include <iostream>

class Pacman : public Caracter
{
private:

    sf::CircleShape pacman;

    bool infected;
    int score;
    bool turning;
    bool in_tunnel;
    Direction final_dir;
    int food_eaten;

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
    corona health;


public:

    Pacman();

    bool invincible;

    void display(sf::RenderWindow &window);
    void restart();

    int getScore();
    double getX();
    double getY();
    Direction getDirection();
    int get_food_eaten();

    void move(Map* map);
    void changeDirection(Direction direction);


};

#endif
