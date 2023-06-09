#include "PlayState.hpp"
#include "EndState.hpp"
#include "../Constants.hpp"


PlayState::PlayState(Game* game_, int level, bool isPaused):
    model(new PlayStateModel(level))
{
    this->game = game_;
    this->stateIdentifier = "PlayState" + to_string(level);
    this->currentLevel = level;
    this->isPaused = isPaused;

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

    this->restartButton = new Button(sf::Vector2f(300.0f, 725.0f), sf::Vector2f(200.0f, 50.0f), "Restart", 
                                   sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200), &font);
}

PlayState::~PlayState()
{
    delete restartButton;
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
        restartButton->update(sf::Vector2f(sf::Mouse::getPosition(game->window)));
        if (restartButton->isPressed)
        {
            this->game->popState();
            this->game->pushState(new PlayState(game, currentLevel, false));
        }
        return;
    }

    model->currentTime += deltaTime;

    // Handle events from the collision queue
    while (!model->collisionQueue.empty() && model->collisionQueue.top().time < model->currentTime)
    {
        CollisionEvent topEvent = model->collisionQueue.top();
        topEvent.handleEvent(model->collisionQueue, model->currentTime);
    }
    model->updateObjects(deltaTime);
    model->removeDeletedObjects();
    scoreText.setString("Score " + to_string(model->gamePoint));
    
    // Load end menu if there are no balls left or no if the player reaches the target point
    if (model->balls.size() == 0 || model->gamePoint >= model->targetPoint)
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

    if(isPaused)
    {
        restartButton->draw(game->window);
        game->window.draw(pauseText);
    }
    else
    {
        game->window.draw(scoreText);
        game->window.draw(stageText);
    }
}

std::string PlayState::getBackgroundImagePath()
{
    return model->backgroundPath;
}

