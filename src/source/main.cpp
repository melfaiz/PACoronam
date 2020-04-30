#include <SFML/Graphics.hpp>
#include <iostream>

#include "constants.hpp"
#include "Game.hpp"
#include "Map.hpp"
#include "window.hpp"
#include <thread>

using namespace std;

int main()
{
    window.setFramerateLimit(GAME_FPS);

    Game game = Game();


    while (window.isOpen())
    {

        
        

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                {window.close();
                return 0;}

            if (event.type == sf::Event::KeyPressed)
                game.start();
            
        }

        window.clear();

        
        
        game.displayGrid();
        

        while (game.isOn())
        {
            
            

            window.clear();
            game.displayGrid();
            game.display();
            
            
            game.readKeyboard();
            
            game.update();
            
            
            
            window.display();
                        


        }     

        
        
        
        window.display();

        






    }

    return 0;
}