#pragma once

#include "State.hpp"
#include "../Button.hpp"
#include "../Game.hpp"

class EndState : public State
{
public:
    EndState(Game* game_, int gamePoint, int level);
    ~EndState();

    void handleInput();
    void update(float deltaTime);
    void draw();
    std::string getBackgroundImagePath();
private:
    int levelPLayed;
    sf::Font font;
    sf::Text result;
    
    Button* restartButton;
    Button* mainmenuButton;
};