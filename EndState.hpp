#pragma once
#include <SFML/Graphics.hpp>

#include "state.hpp"
#include "playState.hpp"
#include "game.hpp"

class EndState : public State
{
    public:
        EndState(Game* game_, int gamePoint);

        void handleInput();
        void update(float deltaTime);
        void draw();
        Game* game;
    private:
        void loadGame();
        sf::Font font;
        sf::Text result;
        sf::Text restartText;
};