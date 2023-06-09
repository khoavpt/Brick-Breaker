#include "States\State.hpp"
#include "Game.hpp"

Game::Game()
{
    // Preload music for each states
    sf::Music* menuMusic = new sf::Music();
    sf::Music* playMusic1 = new sf::Music();
    sf::Music* playMusic2 = new sf::Music();
    menuMusic->setLoop(true);
    playMusic1->setLoop(true);
    playMusic2->setLoop(true);

    menuMusic->openFromFile("static/soundtrack/menu.wav");
    playMusic1->openFromFile("static/soundtrack/play1.wav");
    playMusic2->openFromFile("static/soundtrack/play2.wav");

    stateMusic["MenuState"] = menuMusic;
    stateMusic["PlayState1"] = playMusic1;
    stateMusic["PlayState2"] = playMusic2;

    window.create(sf::VideoMode(600.0f, 960.0f), "Many Brick Breaker", sf::Style::Close);
}

Game::~Game()
{
    // Delete all the loaded music
    for (auto& pair : stateMusic)
    {
        delete pair.second;
    }
    stateMusic.clear();

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

    // Check if the state has music associated with it
    if (stateMusic.count(state->stateIdentifier) > 0)
    {
        if (currentMusic != nullptr) currentMusic->stop();

        currentMusic = stateMusic[state->stateIdentifier];
        currentMusic->play();
    }
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