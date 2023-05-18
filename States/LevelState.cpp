#include <SFML/Graphics.hpp>

#include "LevelState.hpp"
#include "PlayState.hpp"
#include "../Constants.hpp"

LevelState::LevelState(Game* game_)
{
    this->game = game_;
    font.loadFromFile("static/8-bit-in.ttf");
    title.setFont(font);
    title.setCharacterSize(60);
    title.setString("Choose your levels");
    sf::FloatRect textBounds = title.getLocalBounds();
    title.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);

    title.setPosition(BOARD_WIDTH / 2.0f, 150.0f);

    this->level1Button = new Button(sf::Vector2f(150.0f, 350.0f), sf::Vector2f(200.0f, 200.0f), "Level 1", 
                                   sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200), 
                                   &font, "static/preview_level1.png");
                                   
    this->level2Button = new Button(sf::Vector2f(450.0f, 350.0f), sf::Vector2f(200.0f, 200.0f), "Level 2", 
                                   sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200), 
                                   &font, "static/preview_level2.png");
}

LevelState::~LevelState()
{
    delete level1Button;
    delete level2Button;
}

void LevelState::handleInput()
{
    sf::Event event;
    while(game->window.pollEvent(event))
    {
        if (event.type == event.Closed) game->window.close();
    }
}

void LevelState::update(float deltaTime)
{
    level1Button->update(sf::Vector2f(sf::Mouse::getPosition(game->window)));
    level2Button->update(sf::Vector2f(sf::Mouse::getPosition(game->window)));

    if (level1Button->isPressed)
    {
        loadNextState(new PlayState(game, 1));
    }
    else if(level2Button->isPressed) 
    {
        loadNextState(new PlayState(game, 2));
    }
}

void LevelState::draw()
{   
    game->window.draw(title);

    level1Button->draw(game->window);
    level2Button->draw(game->window);
}

std::string LevelState::getBackgroundImagePath()
{
    return "static/1.png";
}

