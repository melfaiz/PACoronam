#include "Character.hpp"

bool Caracter::canMove(Map* map,int i,int j){

    if ( map->getCellType(i, j) == EMPTY or map->getCellType(i, j) == TREAT or map->getCellType(i, j) == PILL or map->getCellType(i, j) == TUNNEL )
    {
        return true;
    }
    return false;
}
