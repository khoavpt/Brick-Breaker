#pragma once
#include "Game.hpp"

class State
{
    public:
        virtual void handleInput() = 0;
        virtual void update(float deltaTime) = 0;
        virtual void draw() = 0;
};