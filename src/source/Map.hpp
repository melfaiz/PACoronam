#ifndef MAP_H
#define MAP_H

#include "window.hpp"

#include <iostream>

typedef enum cellType {
    EMPTY=0,
    FULL,
    HIGH_BAR,
    LOW_BAR,
    RIGHT_BAR,
    LEFT_BAR,
    LEFT_UP_CORNER,
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

private:
    int width;
    int height;

    cellType grid[HEIGHT][WIDTH] = {
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
        {LEFT_DOWN_CORNER,LOW_BAR,LOW_BAR,LOW_BAR,LOW_BAR,LEFT_DOWN,TREAT,RIGHT_BAR,LEFT_DOWN_CORNER,LOW_BAR,LOW_BAR,LEFT_DOWN,TREAT,RIGHT_BAR,LEFT_BAR,TREAT,RIGHT_DOWN,LOW_BAR,LOW_BAR,RIGHT_DOWN_CORNER,LEFT_BAR,TREAT,RIGHT_DOWN,LOW_BAR,LOW_BAR,LOW_BAR,LOW_BAR,RIGHT_DOWN_CORNER},
        {EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,LEFT_BAR,TREAT,RIGHT_BAR,LEFT_UP_CORNER,HIGH_BAR,HIGH_BAR,LEFT_UP,TREAT,RIGHT_UP,LEFT_UP,TREAT,RIGHT_UP,HIGH_BAR,HIGH_BAR,RIGHT_UP_CORNER,LEFT_BAR,TREAT,RIGHT_BAR,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY},
        {EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,LEFT_BAR,TREAT,RIGHT_BAR,LEFT_BAR,TREAT,TREAT,TREAT,TREAT,TREAT,TREAT,TREAT,TREAT,TREAT,TREAT,RIGHT_BAR,LEFT_BAR,TREAT,RIGHT_BAR,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY},
        {EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,LEFT_BAR,TREAT,RIGHT_BAR,LEFT_BAR,TREAT,RIGHT_DOWN,LOW_BAR,LOW_BAR,GATE,GATE,LOW_BAR,LOW_BAR,LEFT_DOWN,TREAT,RIGHT_BAR,LEFT_BAR,TREAT,RIGHT_BAR,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY},
        {HIGH_BAR,HIGH_BAR,HIGH_BAR,HIGH_BAR,HIGH_BAR,LEFT_UP,TREAT,RIGHT_UP,LEFT_UP,TREAT,RIGHT_BAR,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,LEFT_BAR,TREAT,RIGHT_UP,LEFT_UP,TREAT,RIGHT_UP,HIGH_BAR,HIGH_BAR,HIGH_BAR,HIGH_BAR,HIGH_BAR},
        {TREAT,TREAT,TREAT,TREAT,TREAT,TREAT,TREAT,TREAT,TREAT,TREAT,RIGHT_BAR,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,LEFT_BAR,TREAT,TREAT,TREAT,TREAT,TREAT,TREAT,TREAT,TREAT,TREAT,TREAT},
        {LOW_BAR,LOW_BAR,LOW_BAR,LOW_BAR,LOW_BAR,LEFT_DOWN,TREAT,RIGHT_DOWN,LEFT_DOWN,TREAT,RIGHT_BAR,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,LEFT_BAR,TREAT,RIGHT_DOWN,LEFT_DOWN,TREAT,RIGHT_DOWN,LOW_BAR,LOW_BAR,LOW_BAR,LOW_BAR,LOW_BAR},
        {EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,LEFT_BAR,TREAT,RIGHT_BAR,LEFT_BAR,TREAT,RIGHT_UP,HIGH_BAR,HIGH_BAR,HIGH_BAR,HIGH_BAR,HIGH_BAR,HIGH_BAR,LEFT_UP,TREAT,RIGHT_BAR,LEFT_BAR,TREAT,RIGHT_BAR,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY},
        {EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,LEFT_BAR,TREAT,RIGHT_BAR,LEFT_BAR,TREAT,TREAT,TREAT,TREAT,TREAT,TREAT,TREAT,TREAT,TREAT,TREAT,RIGHT_BAR,LEFT_BAR,TREAT,RIGHT_BAR,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY},
        {EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,LEFT_BAR,TREAT,RIGHT_BAR,LEFT_BAR,TREAT,RIGHT_DOWN,LOW_BAR,LOW_BAR,LOW_BAR,LOW_BAR,LOW_BAR,LOW_BAR,LEFT_DOWN,TREAT,RIGHT_BAR,LEFT_BAR,TREAT,RIGHT_BAR,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY},
        {LEFT_UP_CORNER,HIGH_BAR,HIGH_BAR,HIGH_BAR,HIGH_BAR,LEFT_UP,TREAT,RIGHT_UP,LEFT_UP,TREAT,RIGHT_UP,HIGH_BAR,HIGH_BAR,RIGHT_UP_CORNER,LEFT_UP_CORNER,HIGH_BAR,HIGH_BAR,LEFT_UP,TREAT,RIGHT_UP,LEFT_UP,TREAT,RIGHT_UP,HIGH_BAR,HIGH_BAR,HIGH_BAR,HIGH_BAR,RIGHT_UP_CORNER},
        {LEFT_BAR,TREAT,TREAT,TREAT,TREAT,TREAT,TREAT,TREAT,TREAT,TREAT,TREAT,TREAT,TREAT,RIGHT_BAR,LEFT_BAR,TREAT,TREAT,TREAT,TREAT,TREAT,TREAT,TREAT,TREAT,TREAT,TREAT,TREAT,TREAT,RIGHT_BAR},
        {LEFT_BAR,TREAT,RIGHT_DOWN,LOW_BAR,LOW_BAR,LEFT_DOWN,TREAT,RIGHT_DOWN,LOW_BAR,LOW_BAR,LOW_BAR,LEFT_DOWN,TREAT,RIGHT_BAR,LEFT_BAR,TREAT,RIGHT_DOWN,LOW_BAR,LOW_BAR,LOW_BAR,LEFT_DOWN,TREAT,RIGHT_DOWN,LOW_BAR,LOW_BAR,LEFT_DOWN,TREAT,RIGHT_BAR},
        {LEFT_BAR,TREAT,RIGHT_UP,HIGH_BAR,RIGHT_UP_CORNER,LEFT_BAR,TREAT,RIGHT_UP,HIGH_BAR,HIGH_BAR,HIGH_BAR,LEFT_UP,TREAT,RIGHT_UP,LEFT_UP,TREAT,RIGHT_UP,HIGH_BAR,HIGH_BAR,HIGH_BAR,LEFT_UP,TREAT,RIGHT_BAR,LEFT_UP_CORNER,HIGH_BAR,LEFT_UP,TREAT,RIGHT_BAR},
        {LEFT_BAR,PILL,TREAT,TREAT,RIGHT_BAR,LEFT_BAR,TREAT,TREAT,TREAT,TREAT,TREAT,TREAT,TREAT,TREAT,TREAT,TREAT,TREAT,TREAT,TREAT,TREAT,TREAT,TREAT,RIGHT_BAR,LEFT_BAR,TREAT,TREAT,PILL,RIGHT_BAR},
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


public:

    Map(){

    }
    void display();

    void full(int x, int y);

    void high_bar(int x,int y);
    void low_bar(int x,int y);
    void left_bar(int x,int y);
    void right_bar(int x,int y);

    void left_up_corner(int x,int y);
    void left_down_corner(int x,int y);
    void right_up_corner(int x,int y);
    void right_down_corner(int x,int y);

    void left_up(int x,int y);
    void left_down(int x,int y);
    void right_up(int x,int y);
    void right_down(int x,int y);

    void gate(int x,int y);
    void treat(int x,int y);
    void pill(int x,int y);

    cellType getCellType(int x, int y)
    {

        return (cellType)grid[x][y] ;

    }



};


void Map::display(){

    int x,y;

    for (size_t i = 0; i <HEIGHT; i++)
    {
        for (size_t j = 0; j < WIDTH; j++)
        {
            x = j * CELL_SIZE;
            y = i * CELL_SIZE;

            cellType type = getCellType(i,j);

            switch (type)
            {

            case FULL:
                full(x,y);
                break;

            case HIGH_BAR:
                high_bar(x,y);
                break;

            case LOW_BAR:
                low_bar(x,y);
                break;

            case LEFT_BAR:
                left_bar(x,y);
                break;

            case RIGHT_BAR:
                right_bar(x,y);
                break;

            case LEFT_UP_CORNER:
                left_up_corner(x,y);
                break;

            case LEFT_DOWN_CORNER:
                left_down_corner(x,y);
                break;

            case RIGHT_UP_CORNER:
                right_up_corner(x,y);
                break;

            case RIGHT_DOWN_CORNER:
                right_down_corner(x,y);
                break;

            case LEFT_UP:
                left_up(x,y);
                break;

            case LEFT_DOWN:
                left_down(x,y);
                break;

            case RIGHT_DOWN:
                right_down(x,y);
                break;

            case RIGHT_UP:
                right_up(x,y);
                break;

            case GATE:
                gate(x,y);
                break;

            case TREAT:
                treat(x,y);
                break;                

            case PILL:
                pill(x,y);
                break;                

            default:
                break;
            }
        }

    }

}

// **
// **
void Map::full(int x,int y){
    sf::Color color(160, 160, 160);
    sf::RectangleShape shape(sf::Vector2f(CELL_SIZE, CELL_SIZE));
    shape.setPosition(x,y);
    shape.setFillColor (color);
    window.draw(shape);

}

// **
//
void Map::high_bar(int x,int y){
    sf::Color color(160, 160, 160);
    sf::RectangleShape shape(sf::Vector2f(CELL_SIZE, CELL_SIZE/2));
    shape.setPosition(x,y);
    shape.setFillColor (color);
    window.draw(shape);

}


//
// **
void Map::low_bar(int x,int y){
    sf::Color color(160, 160, 160);
    sf::RectangleShape shape(sf::Vector2f(CELL_SIZE, CELL_SIZE/2));
    shape.setPosition(x,y+CELL_SIZE/2);
    shape.setFillColor (color);
    window.draw(shape);

}

// *
// *
void Map::left_bar(int x,int y){
    sf::Color color(160, 160, 160);
    sf::RectangleShape shape(sf::Vector2f(CELL_SIZE/2, CELL_SIZE));
    shape.setPosition(x,y);
    shape.setFillColor (color);
    window.draw(shape);

}

//  *
//  *
void Map::right_bar(int x,int y){
    sf::Color color(160, 160, 160);
    sf::RectangleShape shape(sf::Vector2f(CELL_SIZE/2, CELL_SIZE));
    shape.setPosition(x+CELL_SIZE/2,y);
    shape.setFillColor (color);
    window.draw(shape);

}

// **
// *
void Map::left_up_corner(int x,int y){
    sf::Color color(160, 160, 160);
    sf::RectangleShape shape(sf::Vector2f(CELL_SIZE, CELL_SIZE/2));
    shape.setPosition(x,y);
    shape.setFillColor (color);
    window.draw(shape);

    sf::RectangleShape shape1(sf::Vector2f(CELL_SIZE/2, CELL_SIZE/2));
    shape1.setPosition(x,y+CELL_SIZE/2);
    shape1.setFillColor (color);
    window.draw(shape1);

}

// *
// **
void Map::left_down_corner(int x,int y){
    sf::Color color(160, 160, 160);
    sf::RectangleShape shape(sf::Vector2f(CELL_SIZE/2, CELL_SIZE));
    shape.setPosition(x,y);
    shape.setFillColor (color);
    window.draw(shape);

    sf::RectangleShape shape1(sf::Vector2f(CELL_SIZE/2, CELL_SIZE/2));
    shape1.setPosition(x+CELL_SIZE/2,y+CELL_SIZE/2);
    shape1.setFillColor (color);
    window.draw(shape1);

}

//  *
// **
void Map::right_down_corner(int x,int y){
    sf::Color color(160, 160, 160);
    sf::RectangleShape shape(sf::Vector2f(CELL_SIZE/2, CELL_SIZE));
    shape.setPosition(x+CELL_SIZE/2,y);
    shape.setFillColor (color);
    window.draw(shape);

    sf::RectangleShape shape1(sf::Vector2f(CELL_SIZE/2, CELL_SIZE/2));
    shape1.setPosition(x,y+CELL_SIZE/2);
    shape1.setFillColor (color);
    window.draw(shape1);

}

// **
//  *
void Map::right_up_corner(int x,int y){
    sf::Color color(160, 160, 160);
    sf::RectangleShape shape(sf::Vector2f(CELL_SIZE, CELL_SIZE/2));
    shape.setPosition(x,y);
    shape.setFillColor (color);
    window.draw(shape);

    sf::RectangleShape shape1(sf::Vector2f(CELL_SIZE/2, CELL_SIZE/2));
    shape1.setPosition(x+CELL_SIZE/2,y+CELL_SIZE/2);
    shape1.setFillColor (color);
    window.draw(shape1);

}

// *
//
void Map::left_up(int x,int y){
    sf::Color color(160, 160, 160);
    sf::RectangleShape shape(sf::Vector2f(CELL_SIZE/2, CELL_SIZE/2));
    shape.setPosition(x,y);
    shape.setFillColor (color);
    window.draw(shape);

}

//
// *
void Map::left_down(int x,int y){
    sf::Color color(160, 160, 160);
    sf::RectangleShape shape(sf::Vector2f(CELL_SIZE/2, CELL_SIZE/2));
    shape.setPosition(x,y+CELL_SIZE/2);
    shape.setFillColor (color);
    window.draw(shape);
}

//  *
//
void Map::right_up(int x,int y){
    sf::Color color(160, 160, 160);
    sf::RectangleShape shape(sf::Vector2f(CELL_SIZE/2, CELL_SIZE/2));
    shape.setPosition(x+CELL_SIZE/2,y);
    shape.setFillColor (color);
    window.draw(shape);
}

//
//  *
void Map::right_down(int x,int y){
    sf::Color color(160, 160, 160);
    sf::RectangleShape shape(sf::Vector2f(CELL_SIZE/2, CELL_SIZE/2));
    shape.setPosition(x+CELL_SIZE/2,y+CELL_SIZE/2);
    shape.setFillColor (color);
    window.draw(shape);
}

// Mob's gate
void Map::gate(int x,int y){
    sf::Color color(250,250, 250);
    sf::RectangleShape shape(sf::Vector2f(CELL_SIZE, CELL_SIZE/4));
    shape.setPosition(x,y+2*CELL_SIZE/3);
    shape.setFillColor (color);
    window.draw(shape);

}

// TREATS
void Map::treat(int x,int y){
    sf::Color color(247, 192, 158);
    sf::CircleShape shape(TREAT_RADIUS);
    shape.setPosition(x+CELL_SIZE/2-TREAT_RADIUS,y+CELL_SIZE/2-TREAT_RADIUS);
    shape.setFillColor (color);
    window.draw(shape);

}

// PILLS
void Map::pill(int x,int y){
    sf::Color color(247, 192, 158);
    sf::CircleShape shape(PILL_RADIUS);
    shape.setPosition(x+CELL_SIZE/2-PILL_RADIUS,y+CELL_SIZE/2-PILL_RADIUS);
    shape.setFillColor (color);
    window.draw(shape);

}


#endif
