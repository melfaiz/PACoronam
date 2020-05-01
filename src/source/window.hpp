#ifndef WINDOW_H
#define WINDOW_H

#include <SFML/Graphics.hpp>
#include "constants.hpp"

sf::RenderWindow window(sf::VideoMode(WIDTH * CELL_SIZE, HEIGHT * CELL_SIZE), WINDOW_NAME,sf::Style::Close);


#endif
