#include <SFML/Graphics.hpp>

#include "State.hpp"
#include "Game.hpp"

Game::Game()
{
    window.create(sf::VideoMode(600.0f, 800.0f), "Many Brick Breaker", sf::Style::Close);
}

Game::~Game()
{
    // Delete all the states in the states stack when close the program
    while(!states.empty())
    {
        popState();
    }
}

void Game::popState()
{
    states.pop();
}

void Game::pushState(State* state)
{
    states.push(state);
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
        if (deltaTime > 1.0f / 20.0f) deltaTime = 1.0f / 20.f;

        if (getActiveState() == nullptr) continue;
        getActiveState()->handleInput();
        getActiveState()->update(deltaTime);

        // Clear window
        window.clear(sf::Color(0, 0, 204, 255));

        getActiveState()->draw();
        window.display();
    }
}