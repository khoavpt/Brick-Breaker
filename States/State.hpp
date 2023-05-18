#pragma once
#include "../Game.hpp"

class State
{
public:
    Game* game;
    virtual void handleInput() = 0;
    virtual void update(float deltaTime) = 0;
    virtual void draw() = 0;
    
    void loadNextState(State* nextState)
    {
        this->game->popState();
        this->game->pushState(nextState);
    }

    virtual std::string getBackgroundImagePath() = 0;
    

};