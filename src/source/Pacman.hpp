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
    Direction final_dir;
    int food_eaten;

    //initial parameters :
    const float x_i = 14*CELL_SIZE - PACMAN_RADIUS-0.5;
    const float y_i = y = 26.5*CELL_SIZE - PACMAN_RADIUS;

    int r; // ?


    bool middle(int xy, int yr);
    bool u_move();
    bool eat(Map* map, int i, int j);
    bool angle(Map* map, int i, int j);
    void turn(int xr, int yr);
    void speed_modif(char s);
    corona health;

    bool eat_monster_serie;


public:

    Pacman();

    bool invincible;
    bool in_tunnel;
    corona_state state;

    void set_corona(bool you, Map *map);
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
