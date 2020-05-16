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
        y = 17*CELL_SIZE - MONSTER_SIZE/2 + CELL_SIZE/2;

        direction = WEST;
        mode = on;

        chaseX =  14*CELL_SIZE - CELL_SIZE/2 - MONSTER_SIZE/2 ;        
        chaseY = 13*CELL_SIZE + MONSTER_SIZE;
        
        break;

    case Pokey:
        monster.setFillColor(sf::Color(247, 187, 20));
        x = 16*CELL_SIZE - MONSTER_SIZE/2;
        y = 17*CELL_SIZE - MONSTER_SIZE/2 + CELL_SIZE/2;
        direction = WEST;
        mode = on;

        chaseX = 14*CELL_SIZE ;
        chaseY = 14*CELL_SIZE + CELL_SIZE/2;

        break;

    case Bashful:
        monster.setFillColor(sf::Color::Cyan);
        x = 12*CELL_SIZE - MONSTER_SIZE/2;
        y = 16*CELL_SIZE + MONSTER_SIZE/2;
        direction = WEST;
        mode = on;

        chaseX = 14*CELL_SIZE ;
        chaseY = 14*CELL_SIZE + CELL_SIZE/2;
        break;
    
    case Shadow:
        monster.setFillColor(sf::Color::Red);
        x = 14*CELL_SIZE - MONSTER_SIZE/2;

        y = 14*CELL_SIZE - MONSTER_SIZE/2 + CELL_SIZE/2;


        direction = WEST;

        mode = scatter;
        
        chaseX = 14*CELL_SIZE - CELL_SIZE/2 - MONSTER_SIZE/2 ;
        chaseY = 13*CELL_SIZE + MONSTER_SIZE;

        break;
    
    default:
        break;
    }
    


    
}


bool Monster::canMove(Map* map,int i,int j){

    if ( map->getCellType(i, j) == EMPTY or map->getCellType(i, j) == TREAT or map->getCellType(i, j) == PILL or ( mode == on && map->getCellType(i, j) == GATE) )
    {
        return true;
    }
    return false;
}


void Monster::move(Map* map,Pacman pacman){

        float xr = x+ MONSTER_SIZE/2;
        float yr = y+ MONSTER_SIZE/2;
        int j = xr / CELL_SIZE;
        int i = yr / CELL_SIZE;

        changeDirection(map,pacman);

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




void Monster::changeDirection(Map* map,Pacman pacman){


    float xr = x+ MONSTER_SIZE/2;
    float yr = y+ MONSTER_SIZE/2;

    float xp = pacman.getX();
    float yp = pacman.getY();
    
    if ( mode == on)
    {
            direction = nextDirection;
            nextDirection = start(map);     
        
    }else if( int(xr + CELL_SIZE/2) % CELL_SIZE == 0 and int(yr + CELL_SIZE/2) % CELL_SIZE == 0  )
    
    {


            if(mode == chase){

        chaseX = xp;
        chaseY = yp;

        
            direction = nextDirection;
            nextDirection = chasePoint(map,xp,yp);

        }else if(mode == scatter){

        switch (type)
        {
            case Speedy:
             chaseX = 0;
             chaseY = 0;
            break;

            case Pokey:
             chaseX = 10*CELL_SIZE;
             chaseY = 0;
            break;

            case Bashful:
             chaseY = 20*CELL_SIZE;
             chaseX = 0;
            break;

            case Shadow:
              chaseX =20*CELL_SIZE;
             chaseY = 20*CELL_SIZE;
            break;
        
        default:
            break;
        }

        direction = nextDirection;
        nextDirection = chasePoint(map,chaseX,chaseY);
    

        
    } 

    }

}


Direction Monster::start(Map* map){

    float xr = x+ MONSTER_SIZE/2;
    float yr = y + MONSTER_SIZE/2;

    if( yr == 13*CELL_SIZE + MONSTER_SIZE){ // To adjust monsters in the middle of the cell after exiting the gate
                direction = WEST;
    }

    Direction newDirection;

    switch (type)
    {
    case Speedy:


        if ( yr > chaseY )
        {                
            newDirection = NORTH;
            
        }else if( xr + speed > chaseX)
        {
            newDirection = WEST;
        }

        if( xr == chaseX && yr == chaseY )
        {   
            newDirection = WEST;
            mode = chase;

        }


        break;

    case Pokey:
    
        if( xr - speed > chaseX)
        {
            newDirection = WEST;

        }else if( yr > chaseY){
            newDirection = NORTH;
        }

        if( xr == chaseX && yr == chaseY )
        {   

                newDirection = WEST;    
                mode = chase;
        

        }

       

        break;


    case Bashful:

        if( xr + speed < chaseX)
        {
            newDirection = EAST;

        }else if( yr > chaseY){
            newDirection = NORTH;
        }

        if( xr == chaseX && yr == chaseY )
        {   
            newDirection = WEST;
            mode = chase;
        }

        break;
    
    case Shadow:

        if( xr > chaseX)
        {
            newDirection = WEST;
        }

        if( xr == chaseX && yr == chaseY )
        {   
            newDirection = WEST;
            mode = chase;
        }

        break;
    
    default:
        break;
    }
    

    return newDirection;

}


Direction Monster::chasePoint(Map* map,float xp,float yp){


    float xm = x ;
    float ym = y ;

    // We compute the current cell :
    int jp = (xp + PACMAN_RADIUS ) / CELL_SIZE ;
    int ip = (yp + PACMAN_RADIUS ) / CELL_SIZE ;

    // We compute the current cell :
    int jm = (xm + MONSTER_SIZE/2 ) / CELL_SIZE ;
    int im = (ym + MONSTER_SIZE/2 ) / CELL_SIZE ;

    int jmo = (xm + MONSTER_SIZE/2 ) / CELL_SIZE ;
    int imo = (ym + MONSTER_SIZE/2 ) / CELL_SIZE ;


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
    return minDirection;


}