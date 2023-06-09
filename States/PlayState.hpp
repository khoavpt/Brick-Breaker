#pragma once

#include "PlayStateModel.hpp"
#include "../CollisionEvent.hpp"
#include "../Button.hpp"

class PlayState : public State
{
public:
    PlayState(Game* game_, int level, bool isPaused=true);
    ~PlayState();

    void handleInput();
    void update(float deltaTime);
    void draw();
    std::string getBackgroundImagePath();
    sf::Music* getMusic();
    Game* game;
private:
    bool isPaused = true;
    int currentLevel;

    sf::Font font;
    sf::Text pauseText;
    sf::Text scoreText;
    sf::Text stageText;
    Button* restartButton;

    PlayStateModel* model;
};