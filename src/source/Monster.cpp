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
        x = 14*CELL_SIZE - MONSTER_SIZE/2;
        y = 16*CELL_SIZE + MONSTER_SIZE/2;

        direction = WEST;
    
        break;

    case Pokey:
        monster.setFillColor(sf::Color(247, 187, 20));
        x = 16*CELL_SIZE - MONSTER_SIZE/2;
        y = 16*CELL_SIZE + MONSTER_SIZE/2;
        direction = WEST;
        break;

    case Bashful:
        monster.setFillColor(sf::Color::Cyan);
        x = 12*CELL_SIZE - MONSTER_SIZE/2;
        y = 16*CELL_SIZE + MONSTER_SIZE/2;
        direction = WEST;
        break;
    
    case Shadow:
        monster.setFillColor(sf::Color::Red);
        x = 14*CELL_SIZE - MONSTER_SIZE/2;
        // x = 15*CELL_SIZE + CELL_SIZE/2- MONSTER_SIZE/2;
        y = 13*CELL_SIZE + MONSTER_SIZE/2;
        // direction = EAST;
        nextDirection = WEST;
        break;
    
    default:
        break;
    }
    


    
}



void Monster::move(Map* map,Pacman pacman){

        int xr = x+ MONSTER_SIZE/2;
        int yr = y+ MONSTER_SIZE/2;

        
        if( (xr + CELL_SIZE/2) % CELL_SIZE == 0 and (yr + CELL_SIZE/2) % CELL_SIZE == 0  )
        {
            direction = nextDirection;
            nextDirection = changeDirection(map,pacman);
        }
            

        int j = xr / CELL_SIZE;
        int i = yr / CELL_SIZE;


        switch (direction)
        {
        case NORTH:
            if (isInside(x, y - speed) && canMove(map , (yr - speed - CELL_SIZE/2) / CELL_SIZE , j) )
                y -= speed;
            break;

        case SOUTH:
            if (isInside(x, y + speed) && canMove(map , (yr  + CELL_SIZE/2) / CELL_SIZE  , j) )
                y += speed;
            break;

        case WEST:
            if (isInside(x - speed, y) && canMove(map, i  ,(xr - speed - CELL_SIZE/2) / CELL_SIZE) )
                x -= speed;
            break;

        case EAST:
            if (isInside(x + speed, y) && canMove(map, i  ,(xr  + CELL_SIZE/2) / CELL_SIZE) )
                x += speed;

        default:
            break;
        }

}


void Monster::display(sf::RenderWindow &window){

    monster.setPosition(x,y);            
    window.draw(monster);

}

bool Monster::isInside(int x,int y){

    if ( x <= 0 or x + MONSTER_SIZE > CELL_SIZE*WIDTH or y <= 0 or y+ MONSTER_SIZE > CELL_SIZE*HEIGHT)
    {
        return false;
    }
    return true;
    
}

float getDistanceIndices(int ia,int ja,int ib,int jb){

	float a = ia - ib; //calculating number to square in next step
	float b =  ja  - jb;
	float dist;

	dist = pow(a, 2) + pow(b, 2);       //calculating Euclidean distance
	dist = sqrt(dist);                  

	return dist;
}


Direction Monster::chasePoint(Map* map,float xp,float yp){


    float xm = x ;
    float ym = y ;

    // We compute the current cell :
    int jm = (xm + MONSTER_SIZE/2 ) / CELL_SIZE ;
    int im = (ym + MONSTER_SIZE/2 ) / CELL_SIZE ;

    int jmo = (xm + MONSTER_SIZE/2 ) / CELL_SIZE ;
    int imo = (ym + MONSTER_SIZE/2 ) / CELL_SIZE ;

    // We compute the current cell :
    int jp = (xp + PACMAN_RADIUS ) / CELL_SIZE ;
    int ip = (yp + PACMAN_RADIUS ) / CELL_SIZE ;


    switch (direction)  // ooking one tile ahead of its current tile in its direction of travel.
    {
    case NORTH:
        if( canMove(map,im-1,jm)) // To not choose a wall and get stuck there
            im = im -1;
        break;

    case SOUTH:
        if( canMove(map,im+1,jm))
            im = im+1;
        break;
    case WEST:
        if( canMove(map,im,jm-1))
            jm = jm -1;
        break;

    case EAST:
        if( canMove(map,im,jm+1))
            jm = jm +1;
        break;
    default:
        break;
    }

    Direction minDirection ;   

    float minDistance = 10000000;

    float d = getDistanceIndices(ip,jp,im-1,jm);
    
    if ( d < minDistance and canMove(map,  im-1 , jm ) and !(  im-1 == imo and jm == jmo) )
    {
        minDirection = NORTH;
        minDistance = d;
    } 

    d = getDistanceIndices(ip,jp,im,jm+1);

    if (d < minDistance and canMove(map, im , jm+1) and !( im == imo and jm+1 == jmo) )
    {
        minDirection = EAST;
        minDistance = d;

    }     

    d = getDistanceIndices(ip,jp,im+1,jm);

    if (d < minDistance and canMove(map, im+1,jm) and !( im+1 == imo and jm == jmo))
    {

        minDirection = SOUTH;
        minDistance = d;
        
    }
 
    d = getDistanceIndices(ip,jp,im,jm-1);

    if (d < minDistance and  canMove(map, im,jm-1) and !( im == imo and jm-1 == jmo) )
    {
        
        minDirection = WEST;
        minDistance = d;
        
    }    

    std::cout << "returned : " << minDirection << "\n";
    return minDirection;





}


Direction Monster::changeDirection(Map* map,Pacman pacman){



    float xp = pacman.getX();
    float yp = pacman.getY() ;



  
    return chasePoint(map,xp,yp);

}
