#ifndef PACMAN_H
#define PACMAN_H

#include "window.hpp"
#include "Caracter.hpp"

class Pacman : public Caracter
{
private:
    bool infected;

public:
    Pacman(){


        infected = false;
        x = 50;
        y = 50;

        caracter.setRadius(PACMAN_SIZE);
        caracter.setFillColor(sf::Color(255,238,0));
        
    }

    void display();

};


void Pacman::display(){    

    caracter.setPosition(x,y);
    window.draw(caracter);

}




#endif