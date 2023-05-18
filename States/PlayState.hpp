#pragma once
#include <SFML/Graphics.hpp>

#include "PlayStateModel.hpp"
#include "../CollisionEvent.hpp"

class PlayState : public State
{
public:
    PlayState(Game* game_, int level);
    ~PlayState();

    void handleInput();
    void update(float deltaTime);
    void draw();
    std::string getBackgroundImagePath();
    Game* game;
private:
    bool isPaused = true;
    int currentLevel;

    sf::Font font;
    sf::Text pauseText;
    sf::Text scoreText;
    sf::Text stageText;

    PlayStateModel* model;
};