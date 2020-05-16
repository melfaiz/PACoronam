#ifndef GAME_H
#define GAME_H

#include "Map.hpp"
#include "Pacman.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <iomanip>
#include "Monster.hpp"

class Game
{

public:

    Game();

    void display(sf::RenderWindow &window);
    void readKeyboard(sf::RenderWindow &window);
    void update();
    bool isOn();

private:

    Map map;
    bool gameOn;

    void displayScore(sf::RenderWindow &window);
    void displayGrid(sf::RenderWindow &window);

    Pacman pacman;

    // Monster blinky;
    // Monster pinky;
    // Monster inky;
    // Monster clyde;

};


#endif
