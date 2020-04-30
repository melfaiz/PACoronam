#ifndef PACMAN_H
#define PACMAN_H

#include "window.hpp"
#include "Caracter.hpp"

class Pacman : public Caracter
{
private:
    bool infected;
    sf::CircleShape pacman;

public:
    Pacman(){


        infected = false;
        x = 50;
        y = 50;

        pacman.setRadius(PACMAN_RADIUS);
        pacman.setFillColor(sf::Color(255,238,0));
        
    }

    void display();

};


void Pacman::display(){    

    pacman.setPosition(x,y);
    window.draw(pacman);

}




#endif