#include <SFML/Graphics.hpp>

#include "MenuState.hpp"
#include "PlayState.hpp"
#include "EndState.hpp"

PlayState::PlayState(Game* game_):
    model(new PlayStateModel())
{
    this->game = game_;
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
    model->currentTime += deltaTime;

    // Handle events from the collision queue
    while (!model->collisionQueue.empty() && model->collisionQueue.top().time <= model->currentTime + 0.001f)
    {
        CollisionEvent topEvent = model->collisionQueue.top();
        topEvent.handleEvent(model->collisionQueue, model->currentTime);
    }
    model->updateObjects(deltaTime);
    model->removeDeletedObjects();
    
    // Load end menu if there are no balls left
    if (model->balls.size() == 0) loadEndMenu();
}

void PlayState::draw()
{
    for (list<Ball*>::iterator ballIt = model->balls.begin(); ballIt != model->balls.end(); ++ballIt)
    {
        game->window.draw((*ballIt)->body);
    }
    for (list<Ball*>::iterator buffIt = model->buffs.begin(); buffIt != model->buffs.end(); ++buffIt)
    {
        game->window.draw((*buffIt)->body);
    }
    for (list<Brick*>::iterator brickIt = model->bricks.begin(); brickIt != model->bricks.end(); ++brickIt)
    {
        game->window.draw((*brickIt)->body);
    }
    game->window.draw(model->paddle.body);
    game->window.draw(model->gameScore);
}

void PlayState::loadEndMenu()
{
    this->game->popState();
    this->game->pushState(new EndState(game, model->gamePoint));
}
void PlayState::pauseGame()
{

}

