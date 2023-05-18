#include <SFML/Graphics.hpp>

#include "States\State.hpp"
#include "Game.hpp"

Game::Game()
{
    window.create(sf::VideoMode(600.0f, 960.0f), "Many Brick Breaker", sf::Style::Close);
}

Game::~Game()
{
    // Delete all the states in the states stack when close the program
    while(!states.empty())
    {
        popState();
    }
}

void Game::loadBackgroundImage()
{
    if (getActiveState() == nullptr)
        return;

    std::string backgroundImagePath = getActiveState()->getBackgroundImagePath();
    if (!backgroundTexture.loadFromFile(backgroundImagePath)) {
        return;
    }
    backgroundSprite.setTexture(backgroundTexture);

    // Get the window size
    sf::Vector2u windowSize = window.getSize();

    // Scale the sprite to fit the window size
    backgroundSprite.setScale(static_cast<float>(windowSize.x) / backgroundTexture.getSize().x,
                              static_cast<float>(windowSize.y) / backgroundTexture.getSize().y);
}

void Game::popState()
{
    states.pop();
}

void Game::pushState(State* state)
{
    states.push(state);
    loadBackgroundImage();
}

State* Game::getActiveState()
{
    if (states.empty()) return nullptr;
    return states.top();
}

void Game::gameLoop()
{
    sf::Clock clock;
    float deltaTime = 0.0f;

    while(window.isOpen())
    {
        deltaTime = clock.restart().asSeconds();

        if (getActiveState() == nullptr) continue;
        
        getActiveState()->handleInput();
        getActiveState()->update(deltaTime);

        window.clear();

        window.draw(backgroundSprite);
        getActiveState()->draw();
        
        window.display();
    }
}