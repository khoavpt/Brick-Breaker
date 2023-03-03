#include <SFML/Graphics.hpp>

#include "MenuState.hpp"
#include "playState.hpp"
#include "EndState.hpp"


int MAP_LAYOUT[100] =  {0, 0, 2, 2, 1, 1, 2, 2, 0, 0,
                        0, 0, 2, 2, 2, 2, 2, 2, 0, 0,
                        0, 2, 3, 3, 2, 2, 3, 3, 2, 0,
                        0, 1, 2, 3, 2, 2, 3, 2, 1, 0,
                        0, 1, 2, 2, 1, 1, 2, 2, 1, 0,
                        0, 2, 2, 2, 1, 1, 2, 2, 2, 0,
                        0, 2, 2, 3, 2, 2, 3, 2, 2, 0,
                        0, 0, 2, 2, 3, 3, 2, 2, 0, 0,
                        0, 0, 0, 1, 1, 1, 1, 0, 0, 0,
                        0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

PlayState::PlayState(Game* game_)
{
    gamePoint = 0;
    this->game = game_;
    Ball ball(sf::Vector2f(300.0f, 400.0f));
    balls = {ball};
    bricks = getLayout(MAP_LAYOUT, 10, 10);
}

void PlayState::handleInput()
{
    sf::Event event;
    while(game->window.pollEvent(event))
    {
        if (event.type == event.Closed) game->window.close();
    }
}

void PlayState::update(float deltaTime)
{
    bool canCollide = true;
    // Update paddle and ball movements
    paddle.updateMovement(deltaTime);
    int ballsCount = balls.size();
    if (ballsCount == 0 ) loadEndMenu();
    for (int i = 0; i < ballsCount; i++)
    {
        if (balls[i].isRemoved) balls.erase(balls.begin() + i);
        else balls[i].updateMovement(deltaTime, paddle.body, bricks, canCollide, gamePoint);
    }
}

void PlayState::draw()
{
    game->window.draw(paddle.body);
    for (int i = 0; i < int(bricks.size()); i++)
    {
        game->window.draw(bricks[i].body);
    }
    for (int i = 0; i < int(balls.size()); i++)
    {
        game->window.draw(balls[i].body);
    }
}

void PlayState::loadEndMenu()
{
    this->game->popState();
    this->game->pushState(new EndState(game, gamePoint));
}
void PlayState::pauseGame()
{

}
