#ifndef GAME_H
#define GAME_H


#include "Map.hpp"
#include "Pacman.hpp"
#include "shadow.hpp"
#include "speedy.hpp"
#include "bashful.hpp"
#include "pokey.hpp"
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
    bool isFinish();
    void ready(sf::RenderWindow &window);
    void bad(sf::RenderWindow &window);
    void win(sf::RenderWindow &window);
    bool win_;

private:

    Map map;
    bool gameOn;
    bool finish;
    int step;

    void displayScore(sf::RenderWindow &window);
    void displayGrid(sf::RenderWindow &window);
    void eaten();
    void restart();
    void we_win();

    Pacman pacman;
    shadow Blinky;
    speedy Pinky;
    bashful Inky;
    pokey Clyde;

};


#endif
