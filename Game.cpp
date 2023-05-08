#include <SFML/Graphics.hpp>
#include <string>

#include "State.hpp"
#include "Game.hpp"

Game::Game():
    gameplayHalf(sf::Vector2f(600.f, 800.f)),
    infoHalf(sf::Vector2f(400.f, 800.f))
{
    window.create(sf::VideoMode(1000.0f, 800.0f), "Many Brick Breaker", sf::Style::Close);

    gameplayHalf.setFillColor(sf::Color::Blue);
    gameplayHalf.setOutlineThickness(10.0f);
    gameplayHalf.setOutlineColor(sf::Color::Black);

    infoHalf.setFillColor(sf::Color{160, 160, 160, 255});
    infoHalf.setPosition(sf::Vector2f(600.f, 0.f));

    font.loadFromFile("static/regular.ttf");
    fpsCount.setFont(font);
    fpsCount.setFillColor(sf::Color::Black);
    fpsCount.setCharacterSize(30);
    fpsCount.setPosition(sf::Vector2f(680.0f, 100.0f));
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
        fpsCount.setString("FPS count: " + std::to_string((int)(1 / deltaTime)));

        if (getActiveState() == nullptr) continue;

        getActiveState()->handleInput();
        getActiveState()->update(deltaTime);

        window.clear(sf::Color(0, 0, 204, 255));
        window.draw(infoHalf);
        window.draw(gameplayHalf);
        window.draw(fpsCount);

        getActiveState()->draw();
        window.display();
    }
}