#include "Game.hpp"
using namespace std;

//Restart the game :
void Game::restart(){

    gameOn = false;
    finish = false;
    map.restart();
    step = 0;

    pacman.restart();
    Blinky.restart();
    Pinky.restart();
    Inky.restart();
    Clyde.restart();

}

//Give the state of the game :
bool Game::isOn(){
    return gameOn;
}

bool Game::isFinish(){
    return finish;
}


void Game::bad(sf::RenderWindow &window){

    sf::Font font;
    if (font.loadFromFile(FONT_STYLE))
    {
        sf::Text text;
        text.setFont(font);
        text.setString("Too bad!");
        text.setCharacterSize(FONT_SIZE);
        text.setFillColor(sf::Color(247, 192, 158));
        text.setPosition(195,20*CELL_SIZE);
        window.draw(text);

    }else{
        cout << "Cant find font\n";
    }
}

void Game::ready(sf::RenderWindow &window){

    sf::Font font;
    if (font.loadFromFile(FONT_STYLE))
    {
        sf::Text text;
        text.setFont(font);
        text.setString("Ready?!");
        text.setCharacterSize(FONT_SIZE);
        text.setFillColor(sf::Color(247, 192, 158));
        text.setPosition(205,20*CELL_SIZE);
        window.draw(text);

    }else{
        cout << "Cant find font\n";
    }

}


//Update the game :
void Game::update(){

    pacman.move(&map);
    Blinky.move(&map,pacman);
    Pinky.move(&map,pacman);
    if(pacman.get_food_eaten() >= 30)
        Inky.move(&map,pacman);
    if(step/GAME_FPS > 60 || pacman.get_food_eaten() >= 82)
        Clyde.move(&map,pacman);

    eaten();

    step++;
}

void Game::eaten(){

    int xp = (pacman.getX()+PACMAN_RADIUS)/CELL_SIZE;
    int yp = (pacman.getY()+PACMAN_RADIUS)/CELL_SIZE;

    int xb = (Blinky.getX()+MONSTER_SIZE/2)/CELL_SIZE;
    int yb = (Blinky.getY()+MONSTER_SIZE/2)/CELL_SIZE;

    int xpi = (Pinky.getX()+MONSTER_SIZE/2)/CELL_SIZE;
    int ypi = (Pinky.getY()+MONSTER_SIZE/2)/CELL_SIZE;

    int xI = (Inky.getX()+MONSTER_SIZE/2)/CELL_SIZE;
    int yI = (Inky.getY()+MONSTER_SIZE/2)/CELL_SIZE;

    int xC = (Clyde.getX()+MONSTER_SIZE/2)/CELL_SIZE;
    int yC = (Clyde.getY()+MONSTER_SIZE/2)/CELL_SIZE;

    if(xp == xb && yp == yb && !pacman.in_tunnel){
        if (pacman.invincible){
            Blinky.is_dead();
        }
        else{
            gameOn = false;
            finish = true;
        }
    }

    if(xp == xpi && yp == ypi && !pacman.in_tunnel){
        if (pacman.invincible){
            Pinky.is_dead();
        }
        else{
            gameOn = false;
            finish = true;
        }
    }

    if(xp == xI && yp == yI && !pacman.in_tunnel){
        if (pacman.invincible){
            Inky.is_dead();
        }
        else{
            gameOn = false;
            finish = true;
        }
    }

    if(xp == xC && yp == yC && !pacman.in_tunnel){
        if (pacman.invincible){
            Clyde.is_dead();
        }
        else{
            gameOn = false;
            finish = true;
        }
    }
}


//Display the game board :
void Game::display(sf::RenderWindow &window){

    map.display(window);
    displayScore(window);
    displayGrid(window);

    pacman.display(window);
    Blinky.display(window);
    Pinky.display(window);
    Inky.display(window);
    Clyde.display(window);
}

//Display the score :
void Game::displayScore(sf::RenderWindow &window){

    sf::Font font;
    if (font.loadFromFile(FONT_STYLE))
    {
        sf::Text text;
        text.setFont(font);

        stringstream ss;
        ss << setw(4) << setfill('0') << pacman.getScore();// to change;
        string s = ss.str();

        text.setString(s);
        text.setCharacterSize(FONT_SIZE);
        text.setFillColor(sf::Color(247, 192, 158));
        text.setPosition(230,18);
        window.draw(text);

    }else{
        cout << "Cant find font\n";
    }
}

//Display the grid :
void Game::displayGrid(sf::RenderWindow &window){

    sf::Image image;
    if (!(image.loadFromFile(GRID_IMAGE)))
        cout << "Cannot load image \n";   //Load Image

    sf::Texture texture;
    texture.loadFromImage(image);  //Load Texture from image

    sf::Sprite sprite;
    sprite.setTexture(texture);

    window.draw(sprite);
}

//Read the input :
void Game::readKeyboard(sf::RenderWindow &window){

    sf::Event event;
    while (window.pollEvent(event))
    {

        if (event.type == sf::Event::Closed){
            window.close();
            gameOn = false;
        }

        if (event.type == sf::Event::KeyPressed ){

            gameOn = true;
            switch(event.key.code){

            case(sf::Keyboard::Up):
                pacman.changeDirection(NORTH);
                break;
            case(sf::Keyboard::Down):
                pacman.changeDirection(SOUTH);
                break;
            case(sf::Keyboard::Left):
                pacman.changeDirection(WEST);
                break;
            case(sf::Keyboard::Right):
                pacman.changeDirection(EAST);
                break;
            case(sf::Keyboard::Escape):
                window.close();
                gameOn = false;
                break;
            case(sf::Keyboard::R):
                restart();
            default:
                break;
            }
        }

    }
}

//Constructor :
Game::Game(){

    gameOn = false;
    finish = false;
    step = 0;

}
