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


        game.readKeyboard();

        window.clear();

        

        game.display();


        if (game.isOn())
        {

            game.update();

        }
        
        game.displayGrid();

        window.display();
   


    }

    return 0;
}
