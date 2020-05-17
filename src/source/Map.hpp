#ifndef MAP_H
#define MAP_H

#include "constants.hpp"
#include <SFML/Graphics.hpp>


//Every type of cell :
typedef enum cellType {
    EMPTY=0x00, // 0000 0000
    FULL=0x10, // 0001 0000
    HIGH_BAR=0x11, // 0001 0001
    LOW_BAR=0x12,
    RIGHT_BAR=0x13,
    LEFT_BAR=0x14,
    LEFT_UP_CORNER=0x15,
    LEFT_DOWN_CORNER,
    RIGHT_UP_CORNER,
    RIGHT_DOWN_CORNER,
    LEFT_UP,
    LEFT_DOWN,
    RIGHT_UP,
    RIGHT_DOWN,
    GATE,
    TREAT,
    PILL,

} cellType;


class Map
{

public:

    Map();
    void display(sf::RenderWindow &window);
    cellType getCellType(int i, int j);
    void setCellType(int i, int j, cellType type);

private:

    cellType grid [HEIGHT][WIDTH]= {
        {EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY},
        {EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY},
        {EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY},
        {LEFT_UP_CORNER,HIGH_BAR,HIGH_BAR,HIGH_BAR,HIGH_BAR,HIGH_BAR,HIGH_BAR,HIGH_BAR,HIGH_BAR,HIGH_BAR,HIGH_BAR,HIGH_BAR,HIGH_BAR,RIGHT_UP_CORNER,LEFT_UP_CORNER,HIGH_BAR,HIGH_BAR,HIGH_BAR,HIGH_BAR,HIGH_BAR,HIGH_BAR,HIGH_BAR,HIGH_BAR,HIGH_BAR,HIGH_BAR,HIGH_BAR,HIGH_BAR,RIGHT_UP_CORNER},
        {LEFT_BAR,TREAT,TREAT,TREAT,TREAT,TREAT,TREAT,TREAT,TREAT,TREAT,TREAT,TREAT,TREAT,RIGHT_BAR,LEFT_BAR,TREAT,TREAT,TREAT,TREAT,TREAT,TREAT,TREAT,TREAT,TREAT,TREAT,TREAT,TREAT,RIGHT_BAR},
        {LEFT_BAR,TREAT,RIGHT_DOWN,LOW_BAR,LOW_BAR,LEFT_DOWN,TREAT,RIGHT_DOWN,LOW_BAR,LOW_BAR,LOW_BAR,LEFT_DOWN,TREAT,RIGHT_BAR,LEFT_BAR,TREAT,RIGHT_DOWN,LOW_BAR,LOW_BAR,LOW_BAR,LEFT_DOWN,TREAT,RIGHT_DOWN,LOW_BAR,LOW_BAR,LEFT_DOWN,TREAT,RIGHT_BAR},
        {LEFT_BAR,PILL,RIGHT_BAR,FULL,FULL,LEFT_BAR,TREAT,RIGHT_BAR,FULL,FULL,FULL,LEFT_BAR,TREAT,RIGHT_BAR,LEFT_BAR,TREAT,RIGHT_BAR,FULL,FULL,FULL,LEFT_BAR,TREAT,RIGHT_BAR,FULL,FULL,LEFT_BAR,PILL,RIGHT_BAR},
        {LEFT_BAR,TREAT,RIGHT_UP,HIGH_BAR,HIGH_BAR,LEFT_UP,TREAT,RIGHT_UP,HIGH_BAR,HIGH_BAR,HIGH_BAR,LEFT_UP,TREAT,RIGHT_UP,LEFT_UP,TREAT,RIGHT_UP,HIGH_BAR,HIGH_BAR,HIGH_BAR,LEFT_UP,TREAT,RIGHT_UP,HIGH_BAR,HIGH_BAR,LEFT_UP,TREAT,RIGHT_BAR},
        {LEFT_BAR,TREAT,TREAT,TREAT,TREAT,TREAT,TREAT,TREAT,TREAT,TREAT,TREAT,TREAT,TREAT,TREAT,TREAT,TREAT,TREAT,TREAT,TREAT,TREAT,TREAT,TREAT,TREAT,TREAT,TREAT,TREAT,TREAT,RIGHT_BAR},
        {LEFT_BAR,TREAT,RIGHT_DOWN,LOW_BAR,LOW_BAR,LEFT_DOWN,TREAT,RIGHT_DOWN,LEFT_DOWN,TREAT,RIGHT_DOWN,LOW_BAR,LOW_BAR,LOW_BAR,LOW_BAR,LOW_BAR,LOW_BAR,LEFT_DOWN,TREAT,RIGHT_DOWN,LEFT_DOWN,TREAT,RIGHT_DOWN,LOW_BAR,LOW_BAR,LEFT_DOWN,TREAT,RIGHT_BAR},
        {LEFT_BAR,TREAT,RIGHT_UP,HIGH_BAR,HIGH_BAR,LEFT_UP,TREAT,RIGHT_BAR,LEFT_BAR,TREAT,RIGHT_UP,HIGH_BAR,HIGH_BAR,RIGHT_UP_CORNER,LEFT_UP_CORNER,HIGH_BAR,HIGH_BAR,LEFT_UP,TREAT,RIGHT_BAR,LEFT_BAR,TREAT,RIGHT_UP,HIGH_BAR,HIGH_BAR,LEFT_UP,TREAT,RIGHT_BAR},
        {LEFT_BAR,TREAT,TREAT,TREAT,TREAT,TREAT,TREAT,RIGHT_BAR,LEFT_BAR,TREAT,TREAT,TREAT,TREAT,RIGHT_BAR,LEFT_BAR,TREAT,TREAT,TREAT,TREAT,RIGHT_BAR,LEFT_BAR,TREAT,TREAT,TREAT,TREAT,TREAT,TREAT,RIGHT_BAR},
        {LEFT_DOWN_CORNER,LOW_BAR,LOW_BAR,LOW_BAR,LOW_BAR,LEFT_DOWN,TREAT,RIGHT_BAR,LEFT_DOWN_CORNER,LOW_BAR,LOW_BAR,LEFT_DOWN,EMPTY,RIGHT_BAR,LEFT_BAR,EMPTY,RIGHT_DOWN,LOW_BAR,LOW_BAR,RIGHT_DOWN_CORNER,LEFT_BAR,TREAT,RIGHT_DOWN,LOW_BAR,LOW_BAR,LOW_BAR,LOW_BAR,RIGHT_DOWN_CORNER},
        {EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,LEFT_BAR,TREAT,RIGHT_BAR,LEFT_UP_CORNER,HIGH_BAR,HIGH_BAR,LEFT_UP,EMPTY,RIGHT_UP,LEFT_UP,EMPTY,RIGHT_UP,HIGH_BAR,HIGH_BAR,RIGHT_UP_CORNER,LEFT_BAR,TREAT,RIGHT_BAR,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY},
        {EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,LEFT_BAR,TREAT,RIGHT_BAR,LEFT_BAR,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,RIGHT_BAR,LEFT_BAR,TREAT,RIGHT_BAR,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY},
        {EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,LEFT_BAR,TREAT,RIGHT_BAR,LEFT_BAR,EMPTY,RIGHT_DOWN,LOW_BAR,LOW_BAR,GATE,GATE,LOW_BAR,LOW_BAR,LEFT_DOWN,EMPTY,RIGHT_BAR,LEFT_BAR,TREAT,RIGHT_BAR,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY},
        {HIGH_BAR,HIGH_BAR,HIGH_BAR,HIGH_BAR,HIGH_BAR,LEFT_UP,TREAT,RIGHT_UP,LEFT_UP,EMPTY,RIGHT_BAR,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,LEFT_BAR,EMPTY,RIGHT_UP,LEFT_UP,TREAT,RIGHT_UP,HIGH_BAR,HIGH_BAR,HIGH_BAR,HIGH_BAR,HIGH_BAR},
        {EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,TREAT,EMPTY,EMPTY,EMPTY,RIGHT_BAR,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,LEFT_BAR,EMPTY,EMPTY,EMPTY,TREAT,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY},
        {LOW_BAR,LOW_BAR,LOW_BAR,LOW_BAR,LOW_BAR,LEFT_DOWN,TREAT,RIGHT_DOWN,LEFT_DOWN,EMPTY,RIGHT_BAR,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,LEFT_BAR,EMPTY,RIGHT_DOWN,LEFT_DOWN,TREAT,RIGHT_DOWN,LOW_BAR,LOW_BAR,LOW_BAR,LOW_BAR,LOW_BAR},
        {EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,LEFT_BAR,TREAT,RIGHT_BAR,LEFT_BAR,EMPTY,RIGHT_UP,HIGH_BAR,HIGH_BAR,HIGH_BAR,HIGH_BAR,HIGH_BAR,HIGH_BAR,LEFT_UP,EMPTY,RIGHT_BAR,LEFT_BAR,TREAT,RIGHT_BAR,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY},
        {EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,LEFT_BAR,TREAT,RIGHT_BAR,LEFT_BAR,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,RIGHT_BAR,LEFT_BAR,TREAT,RIGHT_BAR,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY},
        {EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,LEFT_BAR,TREAT,RIGHT_BAR,LEFT_BAR,EMPTY,RIGHT_DOWN,LOW_BAR,LOW_BAR,LOW_BAR,LOW_BAR,LOW_BAR,LOW_BAR,LEFT_DOWN,EMPTY,RIGHT_BAR,LEFT_BAR,TREAT,RIGHT_BAR,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY},
        {LEFT_UP_CORNER,HIGH_BAR,HIGH_BAR,HIGH_BAR,HIGH_BAR,LEFT_UP,TREAT,RIGHT_UP,LEFT_UP,EMPTY,RIGHT_UP,HIGH_BAR,HIGH_BAR,RIGHT_UP_CORNER,LEFT_UP_CORNER,HIGH_BAR,HIGH_BAR,LEFT_UP,EMPTY,RIGHT_UP,LEFT_UP,TREAT,RIGHT_UP,HIGH_BAR,HIGH_BAR,HIGH_BAR,HIGH_BAR,RIGHT_UP_CORNER},
        {LEFT_BAR,TREAT,TREAT,TREAT,TREAT,TREAT,TREAT,TREAT,TREAT,TREAT,TREAT,TREAT,TREAT,RIGHT_BAR,LEFT_BAR,TREAT,TREAT,TREAT,TREAT,TREAT,TREAT,TREAT,TREAT,TREAT,TREAT,TREAT,TREAT,RIGHT_BAR},
        {LEFT_BAR,TREAT,RIGHT_DOWN,LOW_BAR,LOW_BAR,LEFT_DOWN,TREAT,RIGHT_DOWN,LOW_BAR,LOW_BAR,LOW_BAR,LEFT_DOWN,TREAT,RIGHT_BAR,LEFT_BAR,TREAT,RIGHT_DOWN,LOW_BAR,LOW_BAR,LOW_BAR,LEFT_DOWN,TREAT,RIGHT_DOWN,LOW_BAR,LOW_BAR,LEFT_DOWN,TREAT,RIGHT_BAR},
        {LEFT_BAR,TREAT,RIGHT_UP,HIGH_BAR,RIGHT_UP_CORNER,LEFT_BAR,TREAT,RIGHT_UP,HIGH_BAR,HIGH_BAR,HIGH_BAR,LEFT_UP,TREAT,RIGHT_UP,LEFT_UP,TREAT,RIGHT_UP,HIGH_BAR,HIGH_BAR,HIGH_BAR,LEFT_UP,TREAT,RIGHT_BAR,LEFT_UP_CORNER,HIGH_BAR,LEFT_UP,TREAT,RIGHT_BAR},
        {LEFT_BAR,PILL,TREAT,TREAT,RIGHT_BAR,LEFT_BAR,TREAT,TREAT,TREAT,TREAT,TREAT,TREAT,TREAT,EMPTY,EMPTY,TREAT,TREAT,TREAT,TREAT,TREAT,TREAT,TREAT,RIGHT_BAR,LEFT_BAR,TREAT,TREAT,PILL,RIGHT_BAR},
        {LEFT_DOWN_CORNER,LOW_BAR,LEFT_DOWN,TREAT,RIGHT_BAR,LEFT_BAR,TREAT,RIGHT_DOWN,LEFT_DOWN,TREAT,RIGHT_DOWN,LOW_BAR,LOW_BAR,LOW_BAR,LOW_BAR,LOW_BAR,LOW_BAR,LEFT_DOWN,TREAT,RIGHT_DOWN,LEFT_DOWN,TREAT,RIGHT_BAR,LEFT_BAR,TREAT,RIGHT_DOWN,LOW_BAR,RIGHT_DOWN_CORNER},
        {LEFT_UP_CORNER,HIGH_BAR,LEFT_UP,TREAT,RIGHT_UP,LEFT_UP,TREAT,RIGHT_BAR,LEFT_BAR,TREAT,RIGHT_UP,HIGH_BAR,HIGH_BAR,RIGHT_UP_CORNER,LEFT_UP_CORNER,HIGH_BAR,HIGH_BAR,LEFT_UP,TREAT,RIGHT_BAR,LEFT_BAR,TREAT,RIGHT_UP,LEFT_UP,TREAT,RIGHT_UP,HIGH_BAR,RIGHT_UP_CORNER},
        {LEFT_BAR,TREAT,TREAT,TREAT,TREAT,TREAT,TREAT,RIGHT_BAR,LEFT_BAR,TREAT,TREAT,TREAT,TREAT,RIGHT_BAR,LEFT_BAR,TREAT,TREAT,TREAT,TREAT,RIGHT_BAR,LEFT_BAR,TREAT,TREAT,TREAT,TREAT,TREAT,TREAT,RIGHT_BAR},
        {LEFT_BAR,TREAT,RIGHT_DOWN,LOW_BAR,LOW_BAR,LOW_BAR,LOW_BAR,RIGHT_DOWN_CORNER,LEFT_DOWN_CORNER,LOW_BAR,LOW_BAR,LEFT_DOWN,TREAT,RIGHT_BAR,LEFT_BAR,TREAT,RIGHT_DOWN,LOW_BAR,LOW_BAR,RIGHT_DOWN_CORNER,LEFT_DOWN_CORNER,LOW_BAR,LOW_BAR,LOW_BAR,LOW_BAR,LEFT_DOWN,TREAT,RIGHT_BAR},
        {LEFT_BAR,TREAT,RIGHT_UP,HIGH_BAR,HIGH_BAR,HIGH_BAR,HIGH_BAR,HIGH_BAR,HIGH_BAR,HIGH_BAR,HIGH_BAR,LEFT_UP,TREAT,RIGHT_UP,LEFT_UP,TREAT,RIGHT_UP,HIGH_BAR,HIGH_BAR,HIGH_BAR,HIGH_BAR,HIGH_BAR,HIGH_BAR,HIGH_BAR,HIGH_BAR,LEFT_UP,TREAT,RIGHT_BAR},
        {LEFT_BAR,TREAT,TREAT,TREAT,TREAT,TREAT,TREAT,TREAT,TREAT,TREAT,TREAT,TREAT,TREAT,TREAT,TREAT,TREAT,TREAT,TREAT,TREAT,TREAT,TREAT,TREAT,TREAT,TREAT,TREAT,TREAT,TREAT,RIGHT_BAR},
        {LEFT_DOWN_CORNER,LOW_BAR,LOW_BAR,LOW_BAR,LOW_BAR,LOW_BAR,LOW_BAR,LOW_BAR,LOW_BAR,LOW_BAR,LOW_BAR,LOW_BAR,LOW_BAR,LOW_BAR,LOW_BAR,LOW_BAR,LOW_BAR,LOW_BAR,LOW_BAR,LOW_BAR,LOW_BAR,LOW_BAR,LOW_BAR,LOW_BAR,LOW_BAR,LOW_BAR,LOW_BAR,RIGHT_DOWN_CORNER},
        {EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY},
        {EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY},
    };

    void full(int x, int y, sf::RenderWindow &window);

    void high_bar(int x,int y, sf::RenderWindow &window);
    void low_bar(int x,int y, sf::RenderWindow &window);
    void left_bar(int x,int y, sf::RenderWindow &window);
    void right_bar(int x,int y, sf::RenderWindow &window);

    void left_up_corner(int x,int y, sf::RenderWindow &window);
    void left_down_corner(int x,int y, sf::RenderWindow &window);
    void right_up_corner(int x,int y, sf::RenderWindow &window);
    void right_down_corner(int x,int y, sf::RenderWindow &window);

    void left_up(int x,int y, sf::RenderWindow &window);
    void left_down(int x,int y, sf::RenderWindow &window);
    void right_up(int x,int y, sf::RenderWindow &window);
    void right_down(int x,int y, sf::RenderWindow &window);

    void gate(int x,int y, sf::RenderWindow &window);
    void treat(int x,int y, sf::RenderWindow &window);
    void pill(int x,int y, sf::RenderWindow &window);

};


#endif
