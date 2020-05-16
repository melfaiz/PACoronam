#include "constants.hpp"
#include "Game.hpp"
#include <SFML/Graphics.hpp>

int main(){

    //Declaration of the Window :
    sf::RenderWindow window(sf::VideoMode(WIDTH * CELL_SIZE, HEIGHT * CELL_SIZE), WINDOW_NAME,sf::Style::Close);
    window.setFramerateLimit(GAME_FPS);

    //Creation of the game :
    Game game;

    while(window.isOpen()){

        game.readKeyboard(window);

        window.clear();
        game.display(window);

        //If the game is running :
        if (game.isOn())
            game.update();

        window.display();
    }

    return 0;

}
