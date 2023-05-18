#include <SFML/Graphics.hpp>

#include "PlayState.hpp"
#include "EndState.hpp"
#include "../Constants.hpp"


PlayState::PlayState(Game* game_, int level):
    model(new PlayStateModel(level))
{
    this->game = game_;
    this->currentLevel = level;

    font.loadFromFile("static/8-bit-in.ttf");

    pauseText.setFont(font);
    pauseText.setCharacterSize(38);
    pauseText.setString("Press space to pause or resume");
    sf::FloatRect pauseTextBounds = pauseText.getLocalBounds();
    pauseText.setOrigin(pauseTextBounds.left + pauseTextBounds.width / 2.0f, pauseTextBounds.top + pauseTextBounds.height / 2.0f);
    pauseText.setPosition(BOARD_WIDTH / 2.0f, 600.0f);

    scoreText.setFont(font);
    scoreText.setCharacterSize(40);
    scoreText.setString("Score " + to_string(model->gamePoint));
    scoreText.setPosition(10.0f, 10.0f);

    stageText.setFont(font);
    stageText.setCharacterSize(40);
    stageText.setString("Stage " + to_string(model->level));
    stageText.setPosition(460.0f, 10.0f);
}

PlayState::~PlayState()
{
    delete model;
}

void PlayState::handleInput()
{
    sf::Event event;
    while(game->window.pollEvent(event))
    {
        if (event.type == event.Closed) game->window.close();

        if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Space) isPaused = !isPaused;
        }
    }
}

void PlayState::update(float deltaTime)
{
    if(isPaused == true) 
    {
        return;
    }

    model->currentTime += deltaTime;

    // Handle events from the collision queue
    while (!model->collisionQueue.empty() && model->collisionQueue.top().time <= model->currentTime + 0.001f)
    {
        CollisionEvent topEvent = model->collisionQueue.top();
        topEvent.handleEvent(model->collisionQueue, model->currentTime);
    }
    model->updateObjects(deltaTime);
    model->removeDeletedObjects();
    scoreText.setString("Score " + to_string(model->gamePoint));
    
    // Load end menu if there are no balls left
    if (model->balls.size() == 0)
    {
        this->game->popState();
        this->game->pushState(new EndState(game, model->gamePoint, currentLevel));
    }
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

    if(isPaused) game->window.draw(pauseText);
    else
    {
        game->window.draw(scoreText);
        game->window.draw(stageText);
    }
}

std::string PlayState::getBackgroundImagePath()
{
    if(currentLevel == 1) return "static/3.png";
    else if(currentLevel == 2) return "static/4.png";
}

