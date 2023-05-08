#include <SFML/Graphics.hpp>
#include <string>

#include "EndState.hpp"
#include "PlayState.hpp"

EndState::EndState(Game* game_, int gamePoint)
{
    this->game = game_;
    font.loadFromFile("static/regular.ttf");
    result.setFont(font);
    result.setCharacterSize(50);
    result.setString("Score: " + to_string(gamePoint));
    result.setPosition(sf::Vector2f(200.0f, 100.0f));

    restartText.setFont(font);
    restartText.setCharacterSize(30);
    restartText.setString("Press 'space' to try again");
    restartText.setPosition(sf::Vector2f(130.0f, 500.0f));
}

void EndState::loadGame()
{
    this->game->popState();
    this->game->pushState(new PlayState(game));
}

void EndState::handleInput()
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

void EndState::update(float deltaTime)
{

}

void EndState::draw()
{
    game->window.draw(result);
    game->window.draw(restartText);
}

