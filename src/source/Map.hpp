#ifndef MAP_H
#define MAP_H

#include "window.hpp"

typedef enum cellType {
    CELL_EMPTY=0x00,   		//  0000 0000
    CELL_WALL=0x10, 		//  0001 0000

} cellType;

#define CELL(i,j) ( (i) + (j) * WIDTH)

class Map
{

private:
    int width;
    int height;

    cellType grid[WIDTH * HEIGHT] = {
    CELL_EMPTY, CELL_EMPTY, CELL_EMPTY, CELL_EMPTY, CELL_EMPTY, CELL_EMPTY, CELL_EMPTY, CELL_EMPTY, CELL_EMPTY, CELL_EMPTY, 
    CELL_WALL, CELL_WALL, CELL_WALL, CELL_EMPTY, CELL_WALL, CELL_EMPTY, CELL_WALL, CELL_WALL, CELL_WALL, CELL_WALL,
    CELL_EMPTY, CELL_EMPTY, CELL_EMPTY, CELL_EMPTY, CELL_WALL, CELL_EMPTY, CELL_WALL, CELL_EMPTY, CELL_EMPTY, CELL_WALL,
    CELL_EMPTY, CELL_EMPTY, CELL_EMPTY, CELL_EMPTY, CELL_WALL, CELL_EMPTY, CELL_WALL, CELL_EMPTY, CELL_EMPTY, CELL_WALL, 
    CELL_EMPTY, CELL_EMPTY, CELL_EMPTY, CELL_EMPTY, CELL_WALL, CELL_EMPTY, CELL_WALL, CELL_EMPTY, CELL_EMPTY, CELL_WALL, 
    CELL_EMPTY, CELL_EMPTY, CELL_EMPTY, CELL_EMPTY, CELL_WALL, CELL_WALL, CELL_WALL, CELL_EMPTY, CELL_EMPTY, CELL_WALL, 
    CELL_EMPTY, CELL_EMPTY, CELL_EMPTY, CELL_EMPTY, CELL_EMPTY, CELL_EMPTY, CELL_EMPTY , CELL_EMPTY, CELL_EMPTY, CELL_WALL, 
    CELL_EMPTY, CELL_EMPTY, CELL_EMPTY, CELL_EMPTY, CELL_EMPTY, CELL_EMPTY, CELL_EMPTY, CELL_EMPTY,  CELL_EMPTY, CELL_WALL, 
    CELL_EMPTY, CELL_EMPTY, CELL_EMPTY, CELL_EMPTY, CELL_EMPTY, CELL_EMPTY, CELL_EMPTY, CELL_EMPTY, CELL_EMPTY,  CELL_WALL, 
    CELL_EMPTY, CELL_EMPTY, CELL_EMPTY, CELL_EMPTY, CELL_EMPTY, CELL_EMPTY, CELL_EMPTY, CELL_EMPTY, CELL_EMPTY, CELL_WALL, 
    
    };

    
public:

    Map(){

    }
    void display();

    cellType getCellType(int x, int y)
    {
        
        return (cellType)( grid[CELL(x,y)] & 0xf0 ) ;

    }



};


void Map::display(){

    int x,y;

    for (size_t i = 0; i < WIDTH; i++)
    {
        for (size_t j = 0; j < HEIGHT; j++)
        {
            x = i * CELL_SIZE;
            y = j * CELL_SIZE;

            cellType type = getCellType(i,j);

            switch (type)
            {

            case CELL_WALL:
                {

                sf::RectangleShape shape(sf::Vector2f(CELL_SIZE, CELL_SIZE));
                shape.setPosition(x,y);
                window.draw(shape);
                
                }

                break;

            
            default:
                break;
            }
        }
        
    }
    



}



#endif
