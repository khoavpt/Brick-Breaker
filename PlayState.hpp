#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>
#include <queue>

#include "PlayStateModel.hpp"

#include "CollisionEvent.hpp"

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

        PlayStateModel* model;
};