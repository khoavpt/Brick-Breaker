#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

#include "state.hpp"
#include "game.hpp"
#include "paddle.hpp"
#include "ball.hpp"

class PlayState : public State
{
    public:
        PlayState(Game* game_);

        void handleInput();
        void update(float deltaTime);
        void draw();
        Game* game;
    private:
        void pauseGame();
        void loadEndMenu();
        vector <Brick> bricks;
        vector <Ball> balls;
        Paddle paddle;
        int gamePoint;
};