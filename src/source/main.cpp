#include <SFML/Graphics.hpp>
#include <iostream>

#include "constants.hpp"
#include "Game.hpp"
#include "Map.hpp"
#include "window.hpp"

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
                window.close();

            if (event.type == sf::Event::KeyPressed)
                game.start();

        }

        window.clear();

        game.displayMenu();





        while (game.isOn())
        {

            window.clear();

            game.readKeyboard();

            game.update();

            game.display();

            window.display();



        }




        window.display();








    }

    return 0;
}
