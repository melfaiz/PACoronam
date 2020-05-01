#ifndef GAME_H
#define GAME_H


#include "Map.hpp"
#include "Pacman.hpp"
#include "Monster.hpp"
#include <iostream>
#include <iomanip>



class Game
{
private:

    Map map;
    bool gameOn;
    bool gamePaused;

    Pacman pacman;

    Monster blinky;
    Monster pinky;
    Monster inky;
    Monster clyde;


    int score;

public:

    Game() :blinky(Shadow),pinky(Speedy),inky(Bashful),clyde(Pokey)
    {
        gameOn = false;
        gamePaused = false;
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
        map.display();
        pacman.display();


        blinky.display();
        pinky.display();
        inky.display();
        clyde.display();


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

    bool isPaused(){
        return gamePaused;
    }

    void pause(){
        gamePaused = !gamePaused;
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

    pacman.move(&map);
    // blinky.Caracter::move();
    // pinky.Caracter::move();

}

void Game::displayScore(){

    sf::Font font;
    if (font.loadFromFile(FONT_STYLE))
    {
        sf::Text text;
        text.setFont(font);
        
        std::stringstream ss;
        ss << std::setw(4) << std::setfill('0') << pacman.getScore();
        std::string s = ss.str();

        text.setString(s);
        text.setCharacterSize(FONT_SIZE);
        text.setFillColor(sf::Color(247, 192, 158));
        text.setPosition(230,18);
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

        if (event.type == sf::Event::KeyPressed ){

            start();

            switch(event.key.code)
                {

                        case(sf::Keyboard::Up):
                                pacman.changeDirection(NORTH);                                
                                break;
                        case(sf::Keyboard::Down):
                                pacman.changeDirection(SOUTH);
                                break;
                        case(sf::Keyboard::Left):
                                pacman.changeDirection(EAST);
                                break;
                        case(sf::Keyboard::Right):
                                pacman.changeDirection(WEST);
                                break;

                        case(sf::Keyboard::Escape):
                                window.close();
                                exit(); // GAME EXIT
                                break;

                        default:
                                break;
                }
        }



    }




}

#endif
