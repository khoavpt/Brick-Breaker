#include <SFML/Graphics.hpp>
#include <string>

#include "EndState.hpp"
#include "MenuState.hpp"
#include "PlayState.hpp"
#include "../Constants.hpp"

EndState::EndState(Game* game_, int gamePoint, int level)
{
    this->game = game_;
    this->levelPLayed = level;
    font.loadFromFile("static/8-bit-in.ttf");

    result.setFont(font);
    result.setCharacterSize(100);
    result.setString("Score " + to_string(gamePoint));
    sf::FloatRect resultTextBounds = result.getLocalBounds();
    result.setOrigin(resultTextBounds.left + resultTextBounds.width / 2.0f, resultTextBounds.top + resultTextBounds.height / 2.0f);
    result.setPosition(BOARD_WIDTH / 2.0f, 200.0f);

    this->restartButton = new Button(sf::Vector2f(150.0f, 780.0f), sf::Vector2f(200.0f, 50.0f), "Try again", 
                                    sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200), 
                                    &font);
                                   
    this->mainmenuButton = new Button(sf::Vector2f(450.0f, 780.0f), sf::Vector2f(200.0f, 50.0f), "Main menu", 
                                   sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200), 
                                   &font);
}

EndState::~EndState()
{
    delete restartButton;
    delete mainmenuButton;
}

void EndState::handleInput()
{
    sf::Event event;
    while(game->window.pollEvent(event))
    {
        if (event.type == event.Closed) game->window.close();
    }
}

void EndState::update(float deltaTime)
{
    restartButton->update(sf::Vector2f(sf::Mouse::getPosition(game->window)));
    mainmenuButton->update(sf::Vector2f(sf::Mouse::getPosition(game->window)));
    
    if (restartButton->isPressed)
    {
        loadNextState(new PlayState(game, levelPLayed));
    }
    else if(mainmenuButton->isPressed) 
    {
        loadNextState(new MenuState(game));
    }
}

void EndState::draw()
{
    game->window.draw(result);
    
    restartButton->draw(game->window);
    mainmenuButton->draw(game->window);
}

std::string EndState::getBackgroundImagePath()
{
    return "static/1.png";
}

