#include <SFML/Graphics.hpp>

#include "MenuState.hpp"
#include "PlayState.hpp"

MenuState::MenuState(Game* game_)
{
    this->game = game_;
    font.loadFromFile("static/regular.ttf");
    title.setFont(font);
    title.setCharacterSize(50);
    title.setString("Brick Breaker");
    title.setPosition(sf::Vector2f(150.0f, 100.0f));
    instruction.setFont(font);
    instruction.setCharacterSize(30);
    instruction.setString("Press 'space' to continue");
    instruction.setPosition(sf::Vector2f(130.0f, 500.0f));
}

void MenuState::loadGame()
{
    this->game->popState();
    this->game->pushState(new PlayState(game));
}

void MenuState::handleInput()
{
    sf::Event event;
    while(game->window.pollEvent(event))
    {
        if (event.type == event.Closed) game->window.close();
        else if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Space) loadGame();
        }
    }
}

void MenuState::update(float deltaTime)
{

}

void MenuState::draw()
{
    game->window.draw(title);
    game->window.draw(instruction);
}

