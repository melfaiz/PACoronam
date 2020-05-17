
#include "Monster.hpp"

Monster::Monster(monsterType type)
{

    this->type = type;
    speed = 1;
    
    monster.setSize(sf::Vector2f(MONSTER_SIZE, MONSTER_SIZE));

    switch (type)
    {
    case Speedy:

        monster.setFillColor(sf::Color(250, 197, 246));
        x = 14 * CELL_SIZE - MONSTER_SIZE / 2;
        y = 17 * CELL_SIZE - MONSTER_SIZE / 2 + CELL_SIZE / 2;

        direction = WEST;
        mode = on;

        chaseX = 14 * CELL_SIZE - CELL_SIZE / 2 - MONSTER_SIZE / 2;
        chaseY = 13 * CELL_SIZE + MONSTER_SIZE;

        break;

    case Pokey:
        monster.setFillColor(sf::Color(247, 187, 20));
        x = 16 * CELL_SIZE - MONSTER_SIZE / 2;
        y = 17 * CELL_SIZE - MONSTER_SIZE / 2 + CELL_SIZE / 2;

        direction = WEST;
        mode = on;

        chaseX = 14 * CELL_SIZE;
        chaseY = 14 * CELL_SIZE + CELL_SIZE / 2;

        break;

    case Bashful:
        monster.setFillColor(sf::Color::Cyan);
        x = 12 * CELL_SIZE - MONSTER_SIZE / 2;
        y = 16 * CELL_SIZE + MONSTER_SIZE / 2;
        direction = WEST;
        mode = on;

        chaseX = 14 * CELL_SIZE;
        chaseY = 14 * CELL_SIZE + CELL_SIZE / 2;
        break;

    case Shadow:
        monster.setFillColor(sf::Color::Red);
        x = 14 * CELL_SIZE - MONSTER_SIZE / 2;

        y = 14 * CELL_SIZE - MONSTER_SIZE / 2 + CELL_SIZE / 2;

        direction = WEST;

        mode = on;

        chaseX = 14 * CELL_SIZE - CELL_SIZE / 2 - MONSTER_SIZE / 2;
        chaseY = 13 * CELL_SIZE + MONSTER_SIZE;

        break;

    default:
        break;
    }
}

bool Monster::canMove(Map *map, int i, int j)
{

    if (map->getCellType(i, j) == EMPTY or map->getCellType(i, j) == TREAT or map->getCellType(i, j) == PILL or (mode == on && map->getCellType(i, j) == GATE))
    {
        return true;
    }
    return false;
}

void Monster::move(Map *map, Pacman pacman)
{

    float xr = x + MONSTER_SIZE / 2;
    float yr = y + MONSTER_SIZE / 2;
    int j = xr / CELL_SIZE;
    int i = yr / CELL_SIZE;

    changeDirection(map, pacman);

    switch (direction)
    {
    case NORTH:
        if (isInside(x, y - speed) && canMove(map, (yr - speed - CELL_SIZE / 2) / CELL_SIZE, j))
            y -= speed;
        break;

    case SOUTH:
        if (isInside(x, y + speed) && canMove(map, (yr + CELL_SIZE / 2) / CELL_SIZE, j))
            y += speed;
        break;

    case WEST:
        if (isInside(x - speed, y) && canMove(map, i, (xr - speed - CELL_SIZE / 2) / CELL_SIZE))
            x -= speed;
        break;

    case EAST:
        if (isInside(x + speed, y) && canMove(map, i, (xr + CELL_SIZE / 2) / CELL_SIZE))
            x += speed;

    default:
        break;
    }
}

void Monster::display(sf::RenderWindow &window)
{

    monster.setPosition(x, y);
    window.draw(monster);
}

bool Monster::isInside(int x, int y)
{

    if (x <= 0 or x + MONSTER_SIZE > CELL_SIZE * WIDTH or y <= 0 or y + MONSTER_SIZE > CELL_SIZE * HEIGHT)
    {
        return false;
    }
    return true;
}

float Monster::getDistanceIndices(int ia, int ja, int ib, int jb)
{

    float a = ia - ib; //calculating number to square in next step
    float b = ja - jb;
    float dist;

    dist = pow(a, 2) + pow(b, 2); //calculating Euclidean distance
    dist = sqrt(dist);

    return dist;
}

Direction Monster::randomDirection(Map* map){

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

void Monster::changeDirection(Map *map, Pacman pacman)
{


    int jd[] = {0,1,0,-1};
    int id[] = {-1,0,1,0};

    float xr = x + MONSTER_SIZE / 2;
    float yr = y + MONSTER_SIZE / 2;

    float xp = pacman.getX() + PACMAN_RADIUS;
    float yp = pacman.getY() + PACMAN_RADIUS;


    int ip = yp / CELL_SIZE;
    int jp = xp / CELL_SIZE;

    int im = yr / CELL_SIZE;
    int jm = xr / CELL_SIZE;

    Direction pacmanDirection = pacman.getDirection();

    int distance;

    if (mode == on) // Monsters dont obey to being in the middle while exiting the gate
    {


        direction = nextDirection;
        nextDirection = start(map);

    }
    else if (int(xr + CELL_SIZE / 2) % CELL_SIZE == 0 and int(yr + CELL_SIZE / 2) % CELL_SIZE == 0)
    {

        if (mode == chase)
        {
            switch (type)
            {
                case Speedy: //pinky

                    // 4 cells ahead of pacman

                    chaseX = xp + jd[pacmanDirection] * 4 * CELL_SIZE ;
                    chaseY = yp + id[pacmanDirection] * 4 * CELL_SIZE ;

                    break;

                case Pokey:

                    distance = getDistanceIndices(ip,jp,im,jm);

                    if (distance < 8 ) // if pokey is less than 8 cells to pacman he goes home
                    {

                        chaseX =  16 * CELL_SIZE - MONSTER_SIZE / 2;
                        chaseY = 17 * CELL_SIZE - MONSTER_SIZE / 2 + CELL_SIZE / 2;
                    }else{ // he goes for pacman

                        chaseX = xp;
                        chaseY = yp;
                    }

                    break;

                case Bashful:

                    chaseX = 2*xp + jd[pacmanDirection] * 2 * CELL_SIZE;
                    chaseY = 2*yp + id[pacmanDirection] * 2 * CELL_SIZE;

                    break;

                case Shadow:
                    chaseX = xp;
                    chaseY = yp;
                    break;

                default:
                    break;
            }


            direction = nextDirection;


            nextDirection = chasePoint(map, chaseX, chaseY);

        }
        else if (mode == scatter)
        {

            switch (type)
            {
            case Speedy:
                chaseX = 3*CELL_SIZE;
                chaseY = 0;
                break;

            case Pokey:
                chaseX = 0;
                chaseY = 36*CELL_SIZE;
                break;

            case Bashful:
                chaseY = 36 * CELL_SIZE;
                chaseX = 28 *CELL_SIZE;
                break;

            case Shadow:
                chaseX = 26 * CELL_SIZE;
                chaseY = 0;
                break;

            default:
                break;
            }

            direction = nextDirection;
            nextDirection = chasePoint(map, chaseX, chaseY);

        }else if (mode == panic)
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

    }
}

Direction Monster::start(Map *map)
{

    float xr = x + MONSTER_SIZE / 2;
    float yr = y + MONSTER_SIZE / 2;

    if (yr == 13 * CELL_SIZE + MONSTER_SIZE)
    { // To adjust monsters in the middle of the cell after exiting the gate

         direction = WEST;

    }

    Direction newDirection;

    switch (type)
    {
    case Speedy: // pink monster

        if (yr > chaseY)
        {
            newDirection = NORTH;
        }
        else if (xr + speed > chaseX)
        {
            newDirection = WEST;
        }

        if (xr == chaseX && yr == chaseY)
        {

            newDirection = WEST;
            mode =  chase;
        }

        break;

    case Pokey: // orange monster

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

            newDirection = WEST;
            mode =  chase;
        }

        break;

    case Bashful: // Cyan monster

        if (xr + speed < chaseX)
        {
            newDirection = EAST;
        }
        else if (yr > chaseY)
        {
            newDirection = NORTH;
        }

        if (xr == chaseX && yr == chaseY)
        {
            newDirection = WEST;
            mode =  chase;
        }

        break;

    case Shadow: // red monster

        if (xr > chaseX)
        {

            newDirection = WEST;
        }

        if (xr == chaseX && yr == chaseY )
        {
            newDirection = WEST;

            mode =  chase;
        }

        break;

    default:
        break;
    }

    return newDirection;
}

Direction Monster::chasePoint(Map *map, float xp, float yp)
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
