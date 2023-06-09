#include "MenuState.hpp"
#include "LevelState.hpp"
#include "../Constants.hpp"

MenuState::MenuState(Game* game_)
{
    this->game = game_;
    this->stateIdentifier = "MenuState";
    font.loadFromFile("static/8-bit-in.ttf");

    title.setFont(font);
    title.setCharacterSize(140);
    title.setString("  BRICK\nBREAKER");
    sf::FloatRect textBounds = title.getLocalBounds();
    title.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);

    title.setPosition(BOARD_WIDTH / 2.0f, 200.0f);

    this->startButton = new Button(sf::Vector2f(300.0f, 575.0f), sf::Vector2f(200.0f, 50.0f), "Start game", 
                                   sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200), &font);
    this->settingButton = new Button(sf::Vector2f(300.0f, 650.0f), sf::Vector2f(200.0f, 50.0f), "Setting", 
                                   sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200), &font);
    this->exitButton = new Button(sf::Vector2f(300.0f, 725.0f), sf::Vector2f(200.0f, 50.0f), "Exit", 
                                   sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200), &font);
}

MenuState::~MenuState()
{
    delete startButton;
    delete settingButton;
    delete exitButton;
}

void MenuState::handleInput()
{
    sf::Event event;
    while(game->window.pollEvent(event))
    {
        if (event.type == event.Closed) game->window.close();
    }
}

void MenuState::update(float deltaTime)
{
    startButton->update(sf::Vector2f(sf::Mouse::getPosition(game->window)));
    settingButton->update(sf::Vector2f(sf::Mouse::getPosition(game->window)));
    exitButton->update(sf::Vector2f(sf::Mouse::getPosition(game->window)));

    if (startButton->isPressed) loadNextState(new LevelState(game));
    else if(exitButton->isPressed) game->window.close();
}

void MenuState::draw()
{   
    startButton->draw(game->window);
    settingButton->draw(game->window);
    exitButton->draw(game->window);

    game->window.draw(title);
}

std::string MenuState::getBackgroundImagePath()
{
    return "static/state_background/1.png";
}

