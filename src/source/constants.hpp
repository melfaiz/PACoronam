#ifndef CONSTANT_H
#define CONSTANT_H

#define WINDOW_NAME "PACoronam"

#define CELL_SIZE 20

//Grid's size :
#define WIDTH 28
#define HEIGHT 36

//Frame per second :
#define GAME_FPS 60

#define GRID_IMAGE "img/grid.png"

#define FONT_STYLE "img/start.ttf"
#define FONT_SIZE 24

#define MENU_BANNER_TOP 60

//Character's dimension :
#define PACMAN_RADIUS 15
#define MONSTER_SIZE 30

//Food's dimension :
#define TREAT_RADIUS 4
#define PILL_RADIUS 9

#define CELL(i,j) ( (i) + (j) * WIDTH)

//Every direction state a character can have :
typedef enum direction {
	NORTH = 0,
	EAST,  // 1
	SOUTH, // 2
	WEST,   // 3
	INITIAL,
	NOWHERE
} Direction;

//Corona mode :
typedef enum corona_state{

    healthy = 0,
    incubation,
    sick,
    imunate

}corona_state;


//Monster mode :
typedef enum mode {

    chase = 0,
    scatter,
    panic,
    on,
    dead

} Mode;

#define SPEED_REF 1
#define DEBUG false
#define LATEST_VIRUS rand()%3

#endif
