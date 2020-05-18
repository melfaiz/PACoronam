#include "Pacman.hpp"

void Pacman::restart(){

        direction = INITIAL;
        invincible = false;
        turning = false;
        in_tunnel = false;
        x = x_i;
        y = y_i;
        speed = speed_ref;
        score = 0;
        food_eaten = 0;
        health.restart_system();

}

//Engage the procedure to move change the direction of the Pacman :
void Pacman::changeDirection(Direction dir){
    nextDirection = dir;
}


//Modify the speed of the Pacman :
void Pacman::speed_modif(char s){

    static bool p = false;
    //static bool c = false;
    static int counter = 0;

    if(s == 'p'){
        if(!p){
            speed += 0.05*speed;
        }
        p = true;
        invincible = true;
        counter = 7*GAME_FPS;
    }

    if(p){
        counter --;
        if(counter == 0){
            p = false;
            invincible = false;
            counter = 0;
            speed = speed_ref;
        }
    }
}


//Apply the move on the Pac-man :
void Pacman::move(Map* map){

        // We compute the center :
        float xr = x+PACMAN_RADIUS;
        float yr = y+PACMAN_RADIUS;

        // We compute the current cell :
        int j = xr / CELL_SIZE;
        int i = yr / CELL_SIZE;

        //Update of the sped state :
        speed_modif('w');//The input doesn't matter :

        tunnel t;
        in_tunnel = t.is_in_tunnel(xr,direction);

        //If this is the first move of the game :
        if(direction == INITIAL){
            if(nextDirection == EAST){
                x -= speed;
                direction = nextDirection;
            }
            if(nextDirection == WEST){
                x += speed;
                direction = nextDirection;
            }
        }

        //If a turn is engaged :
        else if(turning)
            turn(xr,yr);

        //If we are in the tunnel :
        else if(in_tunnel){
            x = t.in_tunnel(x,speed,direction);
        }
        else{

            //If we don't eat, we are in the first middle of the cell, and we want to turn :
            if(!eat(map,i ,j) && middle(xr,yr) && angle(map,i,j)){
                final_dir = nextDirection;
                turning = true;
                turn(xr,yr);

            }

            //If this is a // move or the same move :
            else{

                if(u_move())
                    direction = nextDirection;

                switch (direction)
                {
                case NORTH:
                    if (canMove(map, (yr - speed - CELL_SIZE/2) / CELL_SIZE  ,j) )
                        y -= speed;
                    else{
                        //If we need to apply a move smaller than the speed :
                        y = (i+0.5)*CELL_SIZE-PACMAN_RADIUS;
                    }
                    break;

                case SOUTH:
                    if (canMove(map, (yr  + speed + CELL_SIZE/2 -1) / CELL_SIZE  ,j) )
                        y += speed;
                    else{
                        //If we need to apply a move smaller than the speed :
                        y = (i+0.5)*CELL_SIZE-PACMAN_RADIUS;
                    }
                    break;

                case WEST:
                    if (canMove(map, i  ,(xr - speed - CELL_SIZE/2) / CELL_SIZE) )
                        x -= speed;
                    else{
                        //If we need to apply a move smaller than the speed :
                        x = (j+0.5)*CELL_SIZE-PACMAN_RADIUS;
                    }
                    break;

                case EAST:
                    if (canMove(map, i  ,(xr  + speed + CELL_SIZE/2 -1) / CELL_SIZE) )
                        x += speed;
                    else{
                        //If we need to apply a move smaller than the speed :
                        x = (j+0.5)*CELL_SIZE-PACMAN_RADIUS;
                    }
                    break;

                default:
                    break;
                }
            }

        }

        nextDirection = NOWHERE;

        //std::cout << "xr : " << x+PACMAN_RADIUS << " yr : " << y+PACMAN_RADIUS << "\n";

}


//Create the asked turn to the Pacman :
void Pacman::turn(int xr, int yr){


    switch(direction){

    //If previously we go to the North :
    case NORTH:
        //To EAst :
        if(final_dir == EAST){
            //If we need to apply a move smaller than the speed :
            if((yr%CELL_SIZE) <= (CELL_SIZE/2 + speed) && (yr%CELL_SIZE) != 0){
                turning = false;
                direction = final_dir;
                x += speed;
                y -= (yr%(CELL_SIZE/2));
                return;
            }
            else{
                x += speed;
                y -= speed;
            }
        }

        //To West
        if(final_dir == WEST){
            //If we need to apply a move smaller than the speed :
            if((yr%CELL_SIZE) <= (CELL_SIZE/2 + speed) && (yr%CELL_SIZE) != 0){
                turning = false;
                direction = final_dir;
                x -= speed;
                y -= (yr%(CELL_SIZE/2));
                //std::cout << "return\n";
                return;
            }
            else{
                x -= speed;
                y -= speed;
            }
        }
        break;

    //If previously we go to the South :
    case SOUTH:
        //To East :
        if(final_dir == EAST){
            //If we need to apply a move smaller than the speed :
            if((yr%CELL_SIZE) >= (CELL_SIZE/2-speed) && (yr%CELL_SIZE) != 0){
                turning = false;
                direction = final_dir;
                x += speed;
                y += CELL_SIZE/2 - (yr%CELL_SIZE);
                //std::cout << "return\n";
                return;
            }
            else{
                x += speed;
                y += speed;
            }
        }

        //To West :
        if(final_dir == WEST){
            //If we need to apply a move smaller than the speed :
            if((yr%CELL_SIZE) >= (CELL_SIZE/2-speed) && (yr%CELL_SIZE) != 0){
                turning = false;
                direction = final_dir;
                x -= speed;
                y += CELL_SIZE/2 - (yr%CELL_SIZE);
                //std::cout << "return\n";
                return;
            }
            else{
                x -= speed;
                y += speed;
            }
        }
        break;
    case EAST:
        if(final_dir == NORTH){
            if((xr%CELL_SIZE) >= (CELL_SIZE/2-speed) && (xr%CELL_SIZE) != 0){
                turning = false;
                direction = final_dir;
                x += CELL_SIZE/2 - (xr%CELL_SIZE);
                y -= speed;
                //std::cout << "return\n";
                return;
            }
            else{
                x += speed;
                y -= speed;
            }
        }

        if(final_dir == SOUTH){
            if((xr%CELL_SIZE) >= (CELL_SIZE/2-speed) && (xr%CELL_SIZE) != 0){
                turning = false;
                direction = final_dir;
                x += CELL_SIZE/2 - (xr%CELL_SIZE);
                y += speed;
                //std::cout << "return\n";
                return;
            }
            else{
                x += speed;
                y += speed;
            }
        }
        break;

    case WEST:
        if(final_dir == NORTH){
            if((xr%CELL_SIZE) <= (CELL_SIZE/2 + speed) && (xr%CELL_SIZE) != 0){
                turning = false;
                direction = final_dir;
                x -= (xr%(CELL_SIZE/2));
                y -= speed;
            //std::cout << "return\n";
            return;
            }
            else{
                x -= speed;
                y -= speed;
            }
        }

        if(final_dir == SOUTH){
            if((xr%CELL_SIZE) <= (CELL_SIZE/2 + speed) && (xr%CELL_SIZE) != 0){
                turning = false;
                direction = final_dir;
                x -= (xr%(CELL_SIZE/2));
                y += speed;
            //std::cout << "return\n";
            return;
            }
            else{
                x -= speed;
                y += speed;
            };
        }
        break;
    default:
        break;
    }

}


//Detect if we want to turn, and if it is possible :
bool Pacman::angle(Map* map,int i, int j){

    if(direction == NORTH || direction == SOUTH){
        if(nextDirection == EAST && canMove(map,i,j+1))
            return true;
        if(nextDirection == WEST && canMove(map,i,j-1))
            return true;
    }

    if(direction == EAST || direction == WEST){
        if(nextDirection == NORTH && canMove(map,i-1,j))
            return true;
        if(nextDirection == SOUTH && canMove(map,i+1,j))
            return true;
    }

    return false;


}


//Detect if Pacman eat :
bool Pacman::eat(Map* map, int i, int j){

    //if we eat :
    if (map->getCellType(i, j) == TREAT)
    {
        score += 10;
        map->setCellType(i, j, EMPTY);
        food_eaten++;
        return true;
    }

    else if (map->getCellType(i, j) == VIRAL_THREAT)
    {
        score += 10;
        map->setCellType(i, j, EMPTY);
        health.state(true);
        food_eaten++;
        return true;
    }


    else if (map->getCellType(i, j) == PILL)
    {
        score += 100;
        map->setCellType(i, j, EMPTY);
        speed_modif('p');
        food_eaten++;
        return true;
    }
    else if (map->getCellType(i,j) == VIRAL_PILL)
    {
        score += 100;
        map->setCellType(i, j, EMPTY);
        health.state(true);
        food_eaten++;
        return true;
    }
    else if (map->getCellType(i,j) == VIRAL_PILL)
    {
        score += 100;
        map->setCellType(i, j, EMPTY);
        health.state(true);
        return true;
    }

    return false;
}


//Detect if the next move is a U move :
bool Pacman::u_move(){

    if(direction == NORTH || direction == SOUTH){
        if(nextDirection == NORTH || nextDirection == SOUTH)
            return true;
    }

    if(direction == EAST || direction == WEST){
        if(nextDirection == EAST || nextDirection == WEST)
            return true;
    }

    return false;
}


//Return true if we are in the first half of a cell
bool Pacman::middle(int xr, int yr){

    switch (direction)
        {
        case NORTH:
            if ((CELL_SIZE/2) <= (yr % CELL_SIZE))
                return true;
            break;

        case SOUTH:
            if ((yr % CELL_SIZE ) <= CELL_SIZE/2)
                return true;
            break;

        case EAST:
            if ((xr % CELL_SIZE) <= CELL_SIZE/2)
                return true;
            break;

        case WEST:
            if ((CELL_SIZE/2) <= (xr % CELL_SIZE))
                return true;
            break;

        default:
            break;
        }

        return false;
}


//Display the Pacman :
void Pacman::display(sf::RenderWindow &window){

    pacman.setPosition(x,y);
    window.draw(pacman);

    //sf::CircleShape point;
    //point.setRadius(1);
    //point.setPosition(x+PACMAN_RADIUS-1,y+PACMAN_RADIUS-1);
    //point.setFillColor(sf::Color::Magenta);
    //window.draw(point);
}


//Give the current score :
int Pacman::getScore(){
    return score;
}

//Give horizontal position :
double Pacman::getX(){
    return x;
}

//Give vertical position :
double Pacman::getY(){
    return y;
}

//Give the direction :
Direction Pacman::getDirection(){
    return direction;
}

int Pacman::get_food_eaten(){
    return food_eaten;
}

//Constructor :
Pacman::Pacman(){

        invincible = false;
        turning = false;
        in_tunnel = false;
        x = x_i;
        y = y_i;
        speed = speed_ref;
        score = 0;
        food_eaten = 0;
        health.restart_system();

        pacman.setRadius(PACMAN_RADIUS);
        pacman.setFillColor(sf::Color(255,238,0));

}
