#include "speedy.hpp"

//Display shadow :
void speedy::display(sf::RenderWindow &window)
{
    speedy_draw.setPosition(x, y);
    window.draw(speedy_draw);
}

void speedy::is_dead(){
    mode = dead;
}

void speedy::change_mode(bool pills, bool restart_){

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
            speedy_draw.setFillColor(sf::Color::Blue);
        if(counter-old_counter >= 6.5*GAME_FPS)
            speedy_draw.setFillColor(sf::Color::White);
        counter++;
        mode = panic;
        speed = 0.77*speed_ref;
        return;
    }
    else{
        speedy_draw.setFillColor(sf::Color(250, 197, 246));
    }

    if(++counter > 39*GAME_FPS)
        counter = 0;
    old_counter = counter;

    if(counter > 9*GAME_FPS && mode != on)
        mode = chase;
    else if(counter <= 9*GAME_FPS && mode != on)
        mode = scatter;

}


//Give a random direction to Shadow :
Direction speedy::randomDirection(Map* map){

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
float speedy::getDistanceIndices(int ia, int ja, int ib, int jb)
{

    float a = ia - ib; //calculating number to square in next step
    float b = ja - jb;
    float dist;

    dist = pow(a, 2) + pow(b, 2); //calculating Euclidean distance
    dist = sqrt(dist);

    return dist;
}

//Move Shadow :
void speedy::move(Map *map, Pacman pacman)
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
bool speedy::canMove(Map *map, int i, int j)
{

    if (map->getCellType(i, j) == EMPTY or map->getCellType(i, j) == TREAT or map->getCellType(i, j) == PILL or (mode == on && map->getCellType(i, j) == GATE) or  map->getCellType(i, j) == VIRAL_PILL or map->getCellType(i, j) == VIRAL_THREAT)
    {
        return true;
    }
    return false;
}


//Put Shadow on the game :
Direction speedy::start(Map *map)
{

    float xr = x + MONSTER_SIZE / 2;
    float yr = y + MONSTER_SIZE / 2;

    //Initial direction of a monster :
    if (yr == 13 * CELL_SIZE + MONSTER_SIZE)
         direction = WEST;


    Direction newDirection;

    if (yr > chaseY)
        newDirection = NORTH;
    else if (xr + speed > chaseX)
        newDirection = WEST;
    if (xr == chaseX && yr == chaseY)
    {
        newDirection = WEST;
        mode =  chase;
    }

    return newDirection;
}


//Compute the direction to take with a target point :
Direction speedy::chasePoint(Map *map, float xp, float yp)
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
void speedy::changeDirection(Map *map, Pacman pacman)
{


    int jd[] = {0,1,0,-1};
    int id[] = {-1,0,1,0};

    float xr = x + MONSTER_SIZE / 2;
    float yr = y + MONSTER_SIZE / 2;

    float xp = pacman.getX() + PACMAN_RADIUS;
    float yp = pacman.getY() + PACMAN_RADIUS;

    Direction pacmanDirection = pacman.getDirection();

    if (mode == on) // Monsters dont obey to being in the middle while exiting the gate
    {
        direction = nextDirection;
        nextDirection = start(map);
    }
    else if (int(xr + CELL_SIZE / 2) % CELL_SIZE == 0 and int(yr + CELL_SIZE / 2) % CELL_SIZE == 0)
    {

        if (mode == chase)
        {
            chaseX = xp + jd[pacmanDirection] * 4 * CELL_SIZE ;
            chaseY = yp + id[pacmanDirection] * 4 * CELL_SIZE ;

            direction = nextDirection;
            nextDirection = chasePoint(map, chaseX, chaseY);
        }
        else if (mode == scatter)
        {
            chaseX = 3*CELL_SIZE;
            chaseY = 0;

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

float speedy::getX(){
    return x;
}

float speedy::getY(){
    return y;
}

//Constructor
speedy::speedy(){

    in_tunnel = false;

    speedy_draw.setSize(sf::Vector2f(MONSTER_SIZE, MONSTER_SIZE));

    speedy_draw.setFillColor(sf::Color(250, 197, 246));

    x = 14 * CELL_SIZE - MONSTER_SIZE / 2;
    y = 17 * CELL_SIZE - MONSTER_SIZE / 2 + CELL_SIZE / 2;
    speed = speed_ref;

    direction = WEST;

    mode = on;

    chaseX = 14 * CELL_SIZE - CELL_SIZE / 2 - MONSTER_SIZE / 2;
    chaseY = 13 * CELL_SIZE + MONSTER_SIZE;
}

//Restart Blinky :
void speedy::restart(){

    in_tunnel = false;
    change_mode(false,true);
    speed = 1;
    speedy_draw.setFillColor(sf::Color(250, 197, 246));

    x = 14 * CELL_SIZE - MONSTER_SIZE / 2;
    y = 17 * CELL_SIZE - MONSTER_SIZE / 2 + CELL_SIZE / 2;

    direction = WEST;

    mode = on;

    chaseX = 14 * CELL_SIZE - CELL_SIZE / 2 - MONSTER_SIZE / 2;
    chaseY = 13 * CELL_SIZE + MONSTER_SIZE;
}
