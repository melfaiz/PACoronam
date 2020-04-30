#ifndef GAME_H
#define GAME_H


#include "Map.hpp"
#include "Pacman.hpp"
#include "Monster.hpp"


class Game
{
private:

    Map map;
    bool gameOn;
    bool debug;

    Pacman pacman;

    Monster blinky;
    Monster pinky;

    int score;
    
public:

    Game() :blinky(Shadow),pinky(Speedy)
    {   
        gameOn = false;
        debug = true;
        score = 0;


    }

    void displayMenu();
    void displayGrid();

    void start(){
        gameOn = true;        

    }

    void update();

    void display(){
        
        displayScore();
        pacman.display();

        blinky.display();
        pinky.display();

    }

    Map getMap(){
        return map;
    }

    bool isOn(){
        return gameOn;
    }

    void readKeyboard();

    void displayScore();

    void exit(){
        gameOn = false;
    }

    bool isDebug(){
        return debug;
    }


};


void Game::displayGrid(){

    sf::Image image;
    if (!(image.loadFromFile(GRID_IMAGE)))
        std::cout << "Cannot load image \n";   //Load Image

    sf::Texture texture;
    texture.loadFromImage(image);  //Load Texture from image

    sf::Sprite sprite;
    sprite.setTexture(texture);   

    window.draw(sprite);
}


void Game::update(){

    pacman.Caracter::move();
    // blinky.Caracter::move();
    // pinky.Caracter::move();

}

void Game::displayScore(){

    sf::Font font;
    if (font.loadFromFile(FONT_STYLE))
    {
        sf::Text text;
        text.setFont(font);

        // std::cout << std::setfill('0') << std::setw(5) << 25;
        text.setString(std::to_string(score));
        text.setCharacterSize(FONT_SIZE);
        text.setFillColor(sf::Color(247, 192, 158));
        text.setPosition(234,18);
        window.draw(text);

    }else{
        std::cout << "Cant find font\n";
    }
}

void Game::readKeyboard(){

    sf::Event event;
    while (window.pollEvent(event))
    {
      
        if (event.type == sf::Event::Closed)
            {window.close();
            exit();} // GAME EXIT

        if (event.type == sf::Event::KeyPressed){
            switch(event.key.code)
                {

                        case(sf::Keyboard::Up):
                                pacman.Caracter::changeDirection(NORTH);
                                
                                break;
                        case(sf::Keyboard::Down):
                                pacman.Caracter::changeDirection(SOUTH);
                                break;
                        case(sf::Keyboard::Left):
                                pacman.Caracter::changeDirection(EAST);
                                break;
                        case(sf::Keyboard::Right):
                                pacman.Caracter::changeDirection(WEST);
                                break;

                        default:
                                break;
                }
        }
           
        
    
    }

}

#endif