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

    Pacman pacman;

    Monster blinky;
    Monster pinky;

    
public:

    Game() :blinky(Shadow),pinky(Speedy)
    {   
        gameOn = false;

    }

    void displayMenu();

    void start(){
        gameOn = true;        

    }

    void update();

    void display(){
        
        
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

};


void Game::displayMenu(){

    sf::Image image;
    if (!(image.loadFromFile(MENU_IMAGE)))
        std::cout << "Cannot load image \n";   //Load Image

    sf::Texture texture;
    texture.loadFromImage(image);  //Load Texture from image

    sf::Sprite sprite;
    sprite.setTexture(texture);   

    window.draw(sprite);
}

void Game::update(){

    pacman.Caracter::move();

}

void Game::readKeyboard(){

    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();

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