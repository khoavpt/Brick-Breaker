#pragma once
#include <SFML/Graphics.hpp>
#include "state.hpp"
#include "playState.hpp"
#include "game.hpp"
class MenuState : public State
{
    public:
        MenuState(Game* game_);

        void handleInput();
        void update(float deltaTime);
        void draw();
        Game* game;
    private:
        void loadGame();
        sf::Font font;
        sf::Text title;
        sf::Text instruction;
};