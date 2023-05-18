#pragma once
#include <SFML/Graphics.hpp>

#include "State.hpp"
#include "../Game.hpp"
#include "../Button.hpp"

class MenuState : public State
{
public:
    MenuState(Game* game_);
    ~MenuState();

    void handleInput();
    void update(float deltaTime);
    void draw();
    std::string getBackgroundImagePath();
private:
    sf::Font font;
    sf::Text title;

    Button* startButton;
    Button* settingButton;
    Button* exitButton;
};