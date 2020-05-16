#include "Character.hpp"

bool Caracter::canMove(Map* map,int i,int j){

    if ( map->getCellType(i, j) == EMPTY or map->getCellType(i, j) == TREAT or map->getCellType(i, j) == PILL)
    {
        return true;
    }
    return false;
}
