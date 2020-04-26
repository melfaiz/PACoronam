#ifndef MAP_H
#define MAP_H

enum cell_type {
    CELL_EMPTY=0x00,   		//  0000 0000
    CELL_WALL=0x10, 		//  0001 0000

};

class Map
{

private:
    int width;
    int height;
    
    vector<vector<int> > grid{ { 0, 0, 16 }, 
                            { 0, 0, 16 }, 
                            { 0, 0, 16 } }; 


public:




};




#endif
