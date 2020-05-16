#include "Game.hpp"


//Constructor :
Game::Game() :blinky(Shadow),pinky(Speedy),inky(Bashful),clyde(Pokey)
{

    gameOn = false;

}



//Give the state of the game :
bool Game::isOn(){
    return gameOn;
}


//Update the game :
void Game::update(){

    pacman.move(&map);

    // blinky.move(&map,pacman);
    pinky.move(&map,pacman);
    // inky.move(&map,pacman);
    // clyde.move(&map,pacman);

}


//Display the game board :
void Game::display(sf::RenderWindow &window){

    map.display(window);
    displayScore(window);
    

    pacman.display(window);

    // blinky.display(window);
    pinky.display(window);
    // inky.display(window);
    // clyde.display(window);

    displayGrid(window);

}

//Display the score :
void Game::displayScore(sf::RenderWindow &window){

    sf::Font font;
    if (font.loadFromFile(FONT_STYLE))
    {
        sf::Text text;
        text.setFont(font);

        std::stringstream ss;
        ss << std::setw(4) << std::setfill('0') << pacman.getScore();// to change;
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

//Display the grid :
void Game::displayGrid(sf::RenderWindow &window){

    sf::Image image;
    if (!(image.loadFromFile(GRID_IMAGE)))
        std::cout << "Cannot load image \n";   //Load Image

    sf::Texture texture;
    texture.loadFromImage(image);  //Load Texture from image

    sf::Sprite sprite;
    sprite.setTexture(texture);

    window.draw(sprite);
}

void Game::start(){
    gameOn = true;
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

            start();

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
            default:
                break;
            }
        }

    }
}

