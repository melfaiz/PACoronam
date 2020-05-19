#include "../include/Game.hpp"
using namespace std;

//Restart the game :
void Game::restart(){

    gameOn = false;
    finish = false;
    win_ = false;
    map.restart();
    step = 0;

    srand(time(NULL));
    corona_ = LATEST_VIRUS;

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


void Game::we_win(){
    win_ = true;
    gameOn = false;
}

void Game::win(sf::RenderWindow &window){

    sf::Font font;
    if (font.loadFromFile(FONT_STYLE))
    {
        sf::Text text;
        text.setFont(font);
        text.setString("You win!");
        text.setCharacterSize(FONT_SIZE);
        text.setFillColor(sf::Color(247, 192, 158));
        text.setPosition(190,20*CELL_SIZE);
        window.draw(text);

    }else{
        cout << "Cant find font\n";
    }

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

    map.update_virus();
    pacman.move(&map);
    Blinky.move(&map,pacman);
    Pinky.move(&map,pacman);

    if(pacman.get_food_eaten() >= 30)
       Inky.move(&map,pacman);
       
    if(step/GAME_FPS > 60 || pacman.get_food_eaten() >= 82)
       Clyde.move(&map,pacman);

    eaten();

    if(pacman.get_food_eaten() >= 244)
        we_win();



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

    static int double_score = 1;

    if(!pacman.invincible)
        double_score = 1;

    if(xp == xb && yp == yb && !pacman.in_tunnel){
        if (pacman.invincible && Blinky.mode != dead){
            Blinky.is_dead();
            pacman.add_score(double_score*100);
            double_score = 2*double_score;
        }
        else{
            if(Blinky.mode != dead){
                gameOn = false;
                finish = true;
            }
        }
    }

    if(xp == xpi && yp == ypi && !pacman.in_tunnel){
        if (pacman.invincible && Pinky.mode != dead){
            Pinky.is_dead();
            pacman.add_score(double_score*100);
            double_score = 2*double_score;
        }
        else{
            if(Pinky.mode != dead){
                gameOn = false;
                finish = true;
            }
        }
    }

    if(xp == xI && yp == yI && !pacman.in_tunnel){
        if (pacman.invincible && Inky.mode != dead){
            Inky.is_dead();
            pacman.add_score(double_score*100);
            double_score = 2*double_score;
        }
        else{
            if(Inky.mode != dead){
                gameOn = false;
                finish = true;
            }
        }
    }

    if(xp == xC && yp == yC && !pacman.in_tunnel){
        if (pacman.invincible && Clyde.mode != dead){
            Clyde.is_dead();
            pacman.add_score(double_score*100);
            double_score = 2*double_score;
        }
        else{
            if(Clyde.mode != dead){
                gameOn = false;
                finish = true;
            }
        }
    }
}


//Display the game board :
void Game::display(sf::RenderWindow &window){

    map.display(window);
    displayScore(window);

    pacman.display(window);
    Blinky.display(window);
    Pinky.display(window);
    Inky.display(window);
    Clyde.display(window);

    if(DEBUG)
        displayGrid(window);
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

        // if (event.type == sf::Event::MouseButtonPressed)

		// {cout << "Button " << event.mouseButton.button << " @ "
        //              << " j :" << sf::Mouse::getPosition(window).x / CELL_SIZE<< ", "
        //              << " i :" << sf::Mouse::getPosition(window).y / CELL_SIZE << "\n";
        // }

        if (event.type == sf::Event::KeyPressed ){

            switch(event.key.code){

            case(sf::Keyboard::Up):
                pacman.changeDirection(NORTH);
                if(!finish)
                    gameOn = true;
                break;
            case(sf::Keyboard::Down):
                pacman.changeDirection(SOUTH);
                if(!finish)
                    gameOn = true;
                break;
            case(sf::Keyboard::Left):
                pacman.changeDirection(WEST);
                if(!finish)
                    gameOn = true;
                break;
            case(sf::Keyboard::Right):
                pacman.changeDirection(EAST);
                if(!finish)
                    gameOn = true;
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
    win_ = false;
    step = 0;

    srand(time(NULL));
    corona_ = LATEST_VIRUS;
}
