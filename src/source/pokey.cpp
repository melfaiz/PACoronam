#include "pokey.hpp"

//Display pokey :
void pokey::display(sf::RenderWindow &window)
{
    pokey_draw.setPosition(x, y);
    window.draw(pokey_draw);
}

void pokey::is_dead(){
    mode = dead;
}

void pokey::change_mode(bool pills,bool restart_){

    static int counter = 0;
    static int old_counter = 0;

    if(restart_)
        counter = 0;

    if(mode == dead){
        if((x == 14 * CELL_SIZE - MONSTER_SIZE / 2) && (y = 17 * CELL_SIZE - MONSTER_SIZE / 2 + CELL_SIZE / 2))
            mode = on;
        if(++counter > 39*GAME_FPS)
            counter = 0;
        old_counter = counter;
        return;
    }

    else if(pills && mode != dead){
        if(counter-old_counter < 6.5*GAME_FPS)
            pokey_draw.setFillColor(sf::Color::Blue);
        if(counter-old_counter >= 6.5*GAME_FPS)
            pokey_draw.setFillColor(sf::Color::White);
        counter++;
        mode = panic;
        speed = 0.77*speed_ref;
        return;
    }
    else{
        pokey_draw.setFillColor(sf::Color(247, 187, 20));
    }

    if(++counter > 39*GAME_FPS)
        counter = 0;
    old_counter = counter;

    if(counter > 9*GAME_FPS && mode != on)
        mode = chase;
    else if(counter <= 9*GAME_FPS && mode != on)
        mode = scatter;

}


//Give a random direction to pokey :
Direction pokey::randomDirection(Map* map){

    int jd[] = {0,1,0,-1};
    int id[] = {-1,0,1,0};

    std::vector<int> directions;


    for (int i = 0; i < 4; i++)
    {
        if ( i != (direction + 2)%4 and i != direction )
        {
            directions.push_back(i);
        }

    }

    int im = (y+ MONSTER_SIZE/2) / CELL_SIZE;
    int jm =(x+ MONSTER_SIZE/2)/ CELL_SIZE;

    Direction dir = (Direction)directions[rand() % 2];
    while ( !canMove(map, im + id[dir] , jm + jd[dir]) )
    {
        dir = (Direction)directions[rand() % 2];
    }

    return dir ;

}


//Give the distance between 2 point :
float pokey::getDistanceIndices(int ia, int ja, int ib, int jb)
{

    float a = ia - ib; //calculating number to square in next step
    float b = ja - jb;
    float dist;

    dist = pow(a, 2) + pow(b, 2); //calculating Euclidean distance
    dist = sqrt(dist);

    return dist;
}

//Move pokey :
void pokey::move(Map *map, Pacman pacman)
{

    float xr = x + MONSTER_SIZE / 2;
    float yr = y + MONSTER_SIZE / 2;
    int j = xr / CELL_SIZE;
    int i = yr / CELL_SIZE;

    if(pacman.invincible)
       change_mode(true,false);
    else{
        change_mode(false,false);
    }

    tunnel t;
    in_tunnel = t.is_in_tunnel(xr,direction);

    if(in_tunnel)
        x = t.in_tunnel(x,speed,direction);

    else{
        changeDirection(map, pacman);

        switch (direction)
        {
        case NORTH:
            if (canMove(map, (yr - speed - CELL_SIZE/2) / CELL_SIZE  ,j) )
                    y -= speed;
            else{
                //If we need to apply a move smaller than the speed :
                y = (i+0.5)*CELL_SIZE-MONSTER_SIZE/2;
            }
            break;

        case SOUTH:
            if (canMove(map, (yr  + speed + CELL_SIZE/2 -1) / CELL_SIZE  ,j) )
                y += speed;
            else{
                //If we need to apply a move smaller than the speed :
                y = (i+0.5)*CELL_SIZE-MONSTER_SIZE/2;
            }
            break;

        case WEST:
            if (canMove(map, i  ,(xr - speed - CELL_SIZE/2) / CELL_SIZE) )
                x -= speed;
            else{
                //If we need to apply a move smaller than the speed :
                x = (j+0.5)*CELL_SIZE-MONSTER_SIZE/2;
            }
            break;

        case EAST:
            if (canMove(map, i  ,(xr  + speed + CELL_SIZE/2 -1) / CELL_SIZE) )
                x += speed;
            else{
                //If we need to apply a move smaller than the speed :
                x = (j+0.5)*CELL_SIZE-MONSTER_SIZE/2;
            }
            break;

        default:
            break;
        }
    }

}


//Can he move to the specific direction :
bool pokey::canMove(Map *map, int i, int j)
{

    if (map->getCellType(i, j) == EMPTY or map->getCellType(i, j) == TREAT or map->getCellType(i, j) == PILL or (mode == on && map->getCellType(i, j) == GATE) or  map->getCellType(i, j) == VIRAL_PILL or map->getCellType(i, j) == VIRAL_THREAT)
    {
        return true;
    }
    return false;
}


//Put pokey on the game :
Direction pokey::start(Map *map)
{

    float xr = x + MONSTER_SIZE / 2;
    float yr = y + MONSTER_SIZE / 2;

    Direction newDirection;

    //Initial direction of a monster :
    if (xr - speed > chaseX)
    {
        newDirection = WEST;
    }
    else if (yr > chaseY)
    {
        newDirection = NORTH;
    }

    if (xr == chaseX && yr == chaseY)
    {
        direction = WEST;
        mode =  chase;
    }

    return newDirection;
}


//Compute the direction to take with a target point :
Direction pokey::chasePoint(Map *map, float xp, float yp)
{

    float xm = x;
    float ym = y;

    // We compute the current cell :
    int jp = (xp + PACMAN_RADIUS) / CELL_SIZE;
    int ip = (yp + PACMAN_RADIUS) / CELL_SIZE;

    // We compute the current cell :
    int jm = (xm + MONSTER_SIZE / 2) / CELL_SIZE;
    int im = (ym + MONSTER_SIZE / 2) / CELL_SIZE;

    int jmo = (xm + MONSTER_SIZE / 2) / CELL_SIZE;
    int imo = (ym + MONSTER_SIZE / 2) / CELL_SIZE;

    switch (nextDirection) // looking one tile ahead of its current tile in its direction of travel.
    {
    case NORTH:
        if (canMove(map, im - 1, jm)) // To not choose a wall and get stuck there
            im = im - 1;
        break;

    case SOUTH:
        if (canMove(map, im + 1, jm))
            im = im + 1;
        break;
    case WEST:
        if (canMove(map, im, jm - 1))
            jm = jm - 1;
        break;

    case EAST:
        if (canMove(map, im, jm + 1))
            jm = jm + 1;
        break;
    default:
        break;
    }

    Direction minDirection;

    float minDistance = 10000000;

    float d = getDistanceIndices(ip, jp, im - 1, jm);

    if (d < minDistance and canMove(map, im - 1, jm) and !(im - 1 == imo and jm == jmo))
    {
        minDirection = NORTH;
        minDistance = d;
    }

    d = getDistanceIndices(ip, jp, im, jm + 1);

    if (d < minDistance and canMove(map, im, jm + 1) and !(im == imo and jm + 1 == jmo))
    {
        minDirection = EAST;
        minDistance = d;
    }

    d = getDistanceIndices(ip, jp, im + 1, jm);

    if (d < minDistance and canMove(map, im + 1, jm) and !(im + 1 == imo and jm == jmo))
    {

        minDirection = SOUTH;
        minDistance = d;
    }

    d = getDistanceIndices(ip, jp, im, jm - 1);

    if (d < minDistance and canMove(map, im, jm - 1) and !(im == imo and jm - 1 == jmo))
    {

        minDirection = WEST;
        minDistance = d;
    }


    return minDirection;
}


//Change the direction:
void pokey::changeDirection(Map *map, Pacman pacman)
{

    float xr = x + MONSTER_SIZE / 2;
    float yr = y + MONSTER_SIZE / 2;

    float xp = pacman.getX() + PACMAN_RADIUS;
    float yp = pacman.getY() + PACMAN_RADIUS;

    int ip = yp / CELL_SIZE;
    int jp = xp / CELL_SIZE;

    int im = yr / CELL_SIZE;
    int jm = xr / CELL_SIZE;

    if (mode == on) // Monsters dont obey to being in the middle while exiting the gate
    {
        direction = nextDirection;
        nextDirection = start(map);
    }
    else if (int(xr + CELL_SIZE / 2) % CELL_SIZE == 0 and int(yr + CELL_SIZE / 2) % CELL_SIZE == 0)
    {

        if (mode == chase)
        {
            int distance = getDistanceIndices(ip,jp,im,jm);

            if (distance < 8 ) // if pokey is less than 8 cells to pacman he goes home
            {
            chaseX =  16 * CELL_SIZE - MONSTER_SIZE / 2;
            chaseY = 17 * CELL_SIZE - MONSTER_SIZE / 2 + CELL_SIZE / 2;
            }
            else{ // he goes for pacman
                chaseX = xp;
                chaseY = yp;
            }

            direction = nextDirection;
            nextDirection = chasePoint(map, chaseX, chaseY);
        }
        else if (mode == scatter)
        {
            chaseX = 0;
            chaseY = 36*CELL_SIZE;

            direction = nextDirection;
            nextDirection = chasePoint(map, chaseX, chaseY);

        }
        else if (mode == panic)
        {

            int Xd[] = {0,1,0,-1};
            int Yd[] = {-1,0,1,0};

            int im = (y+ MONSTER_SIZE/2) / CELL_SIZE;
            int jm = (x+ MONSTER_SIZE/2) / CELL_SIZE;

            if(!canMove(map, im + Yd[direction] , jm + Xd[direction]))
            {
                direction = randomDirection(map) ;
            }
        }
        else if(mode == dead){

            chaseX = 14 * CELL_SIZE - MONSTER_SIZE / 2;
            chaseY = 17 * CELL_SIZE - MONSTER_SIZE / 2 + CELL_SIZE / 2;
            direction = nextDirection;
            nextDirection = chasePoint(map, chaseX, chaseY);
        }

    }
}

float pokey::getX(){
    return x;
}

float pokey::getY(){
    return y;
}

//Constructor
pokey::pokey(){

    in_tunnel = false;

    speed = speed_ref;

    pokey_draw.setSize(sf::Vector2f(MONSTER_SIZE, MONSTER_SIZE));

    pokey_draw.setFillColor(sf::Color(247, 187, 20));

    x = 16 * CELL_SIZE - MONSTER_SIZE / 2;
    y = 17 * CELL_SIZE - MONSTER_SIZE / 2 + CELL_SIZE / 2;
    direction = WEST;
    mode = on;

    chaseX = 14 * CELL_SIZE;
    chaseY = 14 * CELL_SIZE + CELL_SIZE / 2;
}

//Restart pokey :
void pokey::restart(){

    in_tunnel = false;
    change_mode(false,true);
    speed = speed_ref;;
    pokey_draw.setFillColor(sf::Color(247, 187, 20));

    x = 16 * CELL_SIZE - MONSTER_SIZE / 2;
    y = 17 * CELL_SIZE - MONSTER_SIZE / 2 + CELL_SIZE / 2;

    direction = WEST;

    mode = on;

    chaseX = 14 * CELL_SIZE;
    chaseY = 14 * CELL_SIZE + CELL_SIZE / 2;
}
