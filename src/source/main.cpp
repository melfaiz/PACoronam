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

        //If the game is running :
        if (game.isOn()){
            game.display(window);
            game.update();
        }
        else if(game.isFinish()){
            game.bad(window);
            game.display(window);
        }
        else{
            game.ready(window);
            game.display(window);
        }

        window.display();
    }

    return 0;

}
