#pragma once

#include "State.hpp"
#include "../Game.hpp"
#include "../Button.hpp"

class LevelState : public State
{
public:
    LevelState(Game* game_);
    ~LevelState();

    void handleInput();
    void update(float deltaTime);
    void draw();
    std::string getBackgroundImagePath();
private:
    sf::Font font;
    sf::Text title;

    Button* level1Button;
    Button* level2Button;
};