#include "Map.hpp"

//Display the map, without characters :
void Map::display(sf::RenderWindow &window){

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
                full(x,y,window);
                break;

            case HIGH_BAR:
                high_bar(x,y,window);
                break;

            case LOW_BAR:
                low_bar(x,y,window);
                break;

            case LEFT_BAR:
                left_bar(x,y,window);
                break;

            case RIGHT_BAR:
                right_bar(x,y,window);
                break;

            case LEFT_UP_CORNER:
                left_up_corner(x,y,window);
                break;

            case LEFT_DOWN_CORNER:
                left_down_corner(x,y,window);
                break;

            case RIGHT_UP_CORNER:
                right_up_corner(x,y,window);
                break;

            case RIGHT_DOWN_CORNER:
                right_down_corner(x,y,window);
                break;

            case LEFT_UP:
                left_up(x,y,window);
                break;

            case LEFT_DOWN:
                left_down(x,y,window);
                break;

            case RIGHT_DOWN:
                right_down(x,y,window);
                break;

            case RIGHT_UP:
                right_up(x,y,window);
                break;

            case GATE:
                gate(x,y,window);
                break;

            case TREAT:
                treat(x,y,window);
                break;

            case PILL:
                pill(x,y,window);
                break;

            default:
                break;
            }
        }

    }

}

// **
// **
void Map::full(int x,int y, sf::RenderWindow &window){
    sf::Color color(160, 160, 160);
    sf::RectangleShape shape(sf::Vector2f(CELL_SIZE, CELL_SIZE));
    shape.setPosition(x,y);
    shape.setFillColor (color);
    window.draw(shape);

}

// **
//
void Map::high_bar(int x,int y, sf::RenderWindow &window){
    sf::Color color(160, 160, 160);
    sf::RectangleShape shape(sf::Vector2f(CELL_SIZE, CELL_SIZE/2));
    shape.setPosition(x,y);
    shape.setFillColor (color);
    window.draw(shape);

}


//
// **
void Map::low_bar(int x,int y, sf::RenderWindow &window){
    sf::Color color(160, 160, 160);
    sf::RectangleShape shape(sf::Vector2f(CELL_SIZE, CELL_SIZE/2));
    shape.setPosition(x,y+CELL_SIZE/2);
    shape.setFillColor (color);
    window.draw(shape);

}

// *
// *
void Map::left_bar(int x,int y, sf::RenderWindow &window){
    sf::Color color(160, 160, 160);
    sf::RectangleShape shape(sf::Vector2f(CELL_SIZE/2, CELL_SIZE));
    shape.setPosition(x,y);
    shape.setFillColor (color);
    window.draw(shape);

}

//  *
//  *
void Map::right_bar(int x,int y, sf::RenderWindow &window){
    sf::Color color(160, 160, 160);
    sf::RectangleShape shape(sf::Vector2f(CELL_SIZE/2, CELL_SIZE));
    shape.setPosition(x+CELL_SIZE/2,y);
    shape.setFillColor (color);
    window.draw(shape);

}

// **
// *
void Map::left_up_corner(int x,int y, sf::RenderWindow &window){
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
void Map::left_down_corner(int x,int y, sf::RenderWindow &window){
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
void Map::right_down_corner(int x,int y, sf::RenderWindow &window){
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
void Map::right_up_corner(int x,int y, sf::RenderWindow &window){
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
void Map::left_up(int x,int y, sf::RenderWindow &window){
    sf::Color color(160, 160, 160);
    sf::RectangleShape shape(sf::Vector2f(CELL_SIZE/2, CELL_SIZE/2));
    shape.setPosition(x,y);
    shape.setFillColor (color);
    window.draw(shape);

}

//
// *
void Map::left_down(int x,int y, sf::RenderWindow &window){
    sf::Color color(160, 160, 160);
    sf::RectangleShape shape(sf::Vector2f(CELL_SIZE/2, CELL_SIZE/2));
    shape.setPosition(x,y+CELL_SIZE/2);
    shape.setFillColor (color);
    window.draw(shape);
}

//  *
//
void Map::right_up(int x,int y, sf::RenderWindow &window){
    sf::Color color(160, 160, 160);
    sf::RectangleShape shape(sf::Vector2f(CELL_SIZE/2, CELL_SIZE/2));
    shape.setPosition(x+CELL_SIZE/2,y);
    shape.setFillColor (color);
    window.draw(shape);
}

//
//  *
void Map::right_down(int x,int y, sf::RenderWindow &window){
    sf::Color color(160, 160, 160);
    sf::RectangleShape shape(sf::Vector2f(CELL_SIZE/2, CELL_SIZE/2));
    shape.setPosition(x+CELL_SIZE/2,y+CELL_SIZE/2);
    shape.setFillColor (color);
    window.draw(shape);
}

// Mob's gate
void Map::gate(int x,int y, sf::RenderWindow &window){
    sf::Color color(250,250, 250);
    sf::RectangleShape shape(sf::Vector2f(CELL_SIZE, CELL_SIZE/4));
    shape.setPosition(x,y+2*CELL_SIZE/3);
    shape.setFillColor (color);
    window.draw(shape);

}

// TREATS
void Map::treat(int x,int y, sf::RenderWindow &window){
    sf::Color color(247, 192, 158);
    sf::CircleShape shape(TREAT_RADIUS);
    shape.setPosition(x+CELL_SIZE/2-TREAT_RADIUS,y+CELL_SIZE/2-TREAT_RADIUS);
    shape.setFillColor (color);
    window.draw(shape);

}

// PILLS
void Map::pill(int x,int y, sf::RenderWindow &window){
    sf::Color color(247, 192, 158);
    sf::CircleShape shape(PILL_RADIUS);
    shape.setPosition(x+CELL_SIZE/2-PILL_RADIUS,y+CELL_SIZE/2-PILL_RADIUS);
    shape.setFillColor (color);
    window.draw(shape);

}

//Give the type of a cell :
cellType Map::getCellType(int i, int j){

    return (cellType)grid[i][j] ;

}

//Set a cell to a specific type :
void Map::setCellType(int i, int j, cellType type){

        grid[i][j] = type;
}

//Constructor :
Map::Map(){}
