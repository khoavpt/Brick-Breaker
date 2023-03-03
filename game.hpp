#pragma once
#include <SFML/Graphics.hpp>
#include <stack>
#include "State.hpp"

class State;

class Game
{
    public:
        sf::RenderWindow window;

        Game();
        ~Game();

        void pushState(State* state);
        void popState();
        State* getActiveState();
        void gameLoop();
    
    private:
        std::stack <State*> states;
};