#ifndef GAME_H
#define GAME_H

#include "Map.hpp"
#include "Pacman.hpp"
#include "Monster.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <iomanip>

class Game
{

public:

    Game();
    void display(sf::RenderWindow &window);
    void readKeyboard(sf::RenderWindow &window);
    void update();
    bool isOn();
    void ready(sf::RenderWindow &window);

private:

    Map map;
    bool gameOn;

    void displayScore(sf::RenderWindow &window);
    void displayGrid(sf::RenderWindow &window);
    //bool gamePaused;

    Pacman pacman;

    Monster blinky;
    Monster pinky;
    Monster inky;
    Monster clyde;

};


#endif
