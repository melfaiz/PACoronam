#include "../include/shadow.hpp"

//Display shadow :
void shadow::display(sf::RenderWindow &window)
{
    shadow_draw.setPosition(x, y);
    window.draw(shadow_draw);

    if(DEBUG){
        if(state == incubation){
            sf::CircleShape point;
            point.setRadius(4);
            point.setPosition(x+MONSTER_SIZE/2-3,y+MONSTER_SIZE/2-3);
            sf::Color color(250, 0, 246);
            point.setFillColor(color);
            window.draw(point);
        }
        if(state == sick){
            sf::CircleShape point;
            point.setRadius(5);
            point.setPosition(x+MONSTER_SIZE/2-3,y+MONSTER_SIZE/2-3);
            sf::Color color(30, 250, 30);
            point.setFillColor(color);
            window.draw(point);
        }
    }
}

void shadow::is_dead(){
    mode = dead;
    speed = 1.3*SPEED_REF;
}

void shadow::go_home(){

    static bool in_home = false;

    if(!in_home){
        if(x > 14 * CELL_SIZE - MONSTER_SIZE / 2 && direction == WEST){
            x -= speed;
            return;
        }

        else if(x < 14 * CELL_SIZE - MONSTER_SIZE / 2 && direction == EAST){
            x += speed;
            return;
        }
        else{
            x = 14 * CELL_SIZE - MONSTER_SIZE / 2;
        }

        if(y < 17 * CELL_SIZE - MONSTER_SIZE / 2 + CELL_SIZE / 2){
            y += speed;

        }
        else{
            y = 17 * CELL_SIZE - MONSTER_SIZE / 2 + CELL_SIZE / 2;
            in_home = true;
            speed = 0.95*SPEED_REF;
        }
    }
    else{
        if(y > 14 * CELL_SIZE - MONSTER_SIZE / 2 + CELL_SIZE / 2)
            y -= speed;
        else{
            y = 14 * CELL_SIZE - MONSTER_SIZE / 2 + CELL_SIZE / 2;
            in_home = false;
            direction = WEST;
            mode = scatter;
            is_home = false;
        }
    }

}

void shadow::change_mode(bool pills,bool restart_){

    static int counter = -9;
    static int old_counter = 0;

    if(restart_)
        counter = -9;

    if(mode == dead){
        if(++counter > 39*GAME_FPS)
            counter = 0;
        old_counter = counter;
        shadow_draw.setFillColor(sf::Color(255, 255, 255, 128));
        return;
    }

    else if(pills && mode != dead){
        if(counter-old_counter < 6.5*GAME_FPS)
            shadow_draw.setFillColor(sf::Color::Blue);
        if(counter-old_counter >= 6.5*GAME_FPS)
            shadow_draw.setFillColor(sf::Color::White);
        counter++;
        mode = panic;
        speed = 0.77*SPEED_REF;
        return;
    }
    else{
        shadow_draw.setFillColor(sf::Color::Red);
    }

    if(++counter > 39*GAME_FPS)
        counter = 0;
    old_counter = counter;

    if(counter <= 30*GAME_FPS){
        mode = chase;
        speed = 0.95*SPEED_REF;
    }
    else if(counter > 30*GAME_FPS){
        mode = scatter;
        speed = 0.95*SPEED_REF;
    }


    float xr = x + MONSTER_SIZE / 2;
    float yr = y + MONSTER_SIZE / 2;

    int i = yr / CELL_SIZE;

    if((xr <= 5.5*CELL_SIZE && i == 17) || (xr >= 21.5*CELL_SIZE && i == 17))
        speed = 0.55*SPEED_REF;

}


//Give a random direction to Shadow :
Direction shadow::randomDirection(Map* map){

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
float shadow::getDistanceIndices(int ia, int ja, int ib, int jb)
{

    float a = ia - ib; //calculating number to square in next step
    float b = ja - jb;
    float dist;

    dist = pow(a, 2) + pow(b, 2); //calculating Euclidean distance
    dist = sqrt(dist);

    return dist;
}

//Move Shadow :
void shadow::move(Map *map, Pacman pacman)
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

    if((mode == dead && i == 14 && j == 14) || is_home){
        is_home = true;
        go_home();
        return;
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

    if(map->getCellType(i,j) == TREAT && (state == incubation || state == sick))
        map->setCellType(i,j,VIRAL_TREAT);
    if(map->getCellType(i,j) == PILL && (state == incubation || state == sick))
        map->setCellType(i,j,VIRAL_PILL);

    if((map->getCellType(i,j) == VIRAL_TREAT || map->getCellType(i,j) == VIRAL_PILL) && state == healthy)
        state = incubation;

}


//Can he move to the specific direction :
bool shadow::canMove(Map *map, int i, int j)
{

    if ( ( i == 25 or i == 13) and ( j == 15 or j == 12) and direction % 2 == 1) // CANT GO UP
    {
        return false;

    }



    if (map->getCellType(i, j) == EMPTY or map->getCellType(i, j) == TREAT or map->getCellType(i, j) == PILL or (mode == on && map->getCellType(i, j) == GATE) or  map->getCellType(i, j) == VIRAL_PILL or map->getCellType(i, j) == VIRAL_TREAT)
    {

            return true;


    }

    return false;
}


//Put Shadow on the game :
Direction shadow::start(Map *map)
{

    float xr = x + MONSTER_SIZE / 2;
    float yr = y + MONSTER_SIZE / 2;

    //Initial direction of a monster :
    if (yr == 13 * CELL_SIZE + MONSTER_SIZE)
         direction = WEST;


    Direction newDirection;

    if (xr > chaseX)
        newDirection = WEST;

    if (xr == chaseX && yr == chaseY ){
        newDirection = WEST;
        mode =  chase;
    }

    return newDirection;
}


//Compute the direction to take with a target point :
Direction shadow::chasePoint(Map *map, float xp, float yp)
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
void shadow::changeDirection(Map *map, Pacman pacman)
{

    float xr = x + MONSTER_SIZE / 2;
    float yr = y + MONSTER_SIZE / 2;

    float xp = pacman.getX() + PACMAN_RADIUS;
    float yp = pacman.getY() + PACMAN_RADIUS;

    if (mode == on) // Monsters dont obey to being in the middle while exiting the gate
    {
        direction = nextDirection;
        nextDirection = start(map);
    }
    else if (int(xr + CELL_SIZE / 2) % CELL_SIZE == 0 and int(yr + CELL_SIZE / 2) % CELL_SIZE == 0)
    {

        if (mode == chase)
        {
            chaseX = xp;
            chaseY = yp;

            direction = nextDirection;
            nextDirection = chasePoint(map, chaseX, chaseY);
        }
        else if (mode == scatter)
        {
            chaseX = 26 * CELL_SIZE;
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

float shadow::getX(){
    return x;
}

float shadow::getY(){
    return y;
}

//Constructor
shadow::shadow(){

    in_tunnel = false;
    is_home = false;
    state = healthy;

    shadow_draw.setSize(sf::Vector2f(MONSTER_SIZE, MONSTER_SIZE));

    shadow_draw.setFillColor(sf::Color::Red);

    x = 14 * CELL_SIZE - MONSTER_SIZE / 2;
    y = 14 * CELL_SIZE - MONSTER_SIZE / 2 + CELL_SIZE / 2;
    speed = 0.95*SPEED_REF;

    direction = WEST;

    mode = on;

    chaseX = 14 * CELL_SIZE - CELL_SIZE / 2 - MONSTER_SIZE / 2;
    chaseY = 13 * CELL_SIZE + MONSTER_SIZE;
}

//Restart Blinky :
void shadow::restart(){

    in_tunnel = false;
    change_mode(false,true);
    is_home = false;
    speed = SPEED_REF;
    state = healthy;
    shadow_draw.setFillColor(sf::Color::Red);
    state = healthy;

    x = 14 * CELL_SIZE - MONSTER_SIZE / 2;
    y = 14 * CELL_SIZE - MONSTER_SIZE / 2 + CELL_SIZE / 2;

    direction = WEST;

    mode = on;

    chaseX = 14 * CELL_SIZE - CELL_SIZE / 2 - MONSTER_SIZE / 2;
    chaseY = 13 * CELL_SIZE + MONSTER_SIZE;
}
