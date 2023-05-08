#include "PlayStateModel.hpp"
#include "Constants.hpp"

int MAP_LAYOUT[100] =  {0, 0, 2, 2, 1, 1, 2, 2, 0, 0,
                        0, 0, 2, 2, 2, 2, 2, 2, 0, 0,
                        0, 2, 3, 3, 2, 2, 3, 3, 2, 0,
                        0, 1, 2, 3, 2, 2, 3, 2, 1, 0,
                        0, 1, 2, 2, 1, 1, 2, 2, 1, 0,
                        0, 2, 2, 2, 1, 1, 2, 2, 2, 0,
                        0, 3, 2, 3, 2, 2, 3, 2, 3, 0,
                        0, 0, 2, 2, 3, 3, 2, 2, 0, 0,
                        0, 0, 0, 1, 1, 1, 1, 0, 0, 0,
                        0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

PlayStateModel::PlayStateModel():
    paddle(this)
{
    gamePoint = 0;
    font.loadFromFile("static/regular.ttf");
    gameScore.setFont(font);
    gameScore.setFillColor(sf::Color::Black);
    gameScore.setCharacterSize(30);
    gameScore.setPosition(sf::Vector2f(700.0f, 300.0f));

    Ball* ball10 = new Ball(sf::Vector2f(300.0f, 500.0f), sf::Vector2f(BALL_ORGINAL_VELOCITY_X, BALL_ORGINAL_VELOCITY_Y), 0);
    balls = {ball10};
    
    walls = {new Wall(0), new Wall(1), new Wall(2), new Wall(3)};
    bricks = getLayout(MAP_LAYOUT, 10, 10);
    // bricks = {new Brick(3, 1, sf::Vector2f(300.0f, 100.0f), this)};

    // Add every collision events between colliders into collision queue
    for (list<Ball*>::iterator ballIt = balls.begin(); ballIt != balls.end(); ballIt++)
    {
        for (list<Ball*>::iterator ballIt2 = next(ballIt); ballIt2 != balls.end(); ballIt2++)
        {
            collisionQueue.push({(*ballIt)->timeToCollision(*ballIt2), *ballIt2, *ballIt});
        }
        for (list<Brick*>::iterator brickIt = bricks.begin(); brickIt != bricks.end(); brickIt++)
        {
            collisionQueue.push({(*brickIt)->timeToCollision(*ballIt), *brickIt, *ballIt});
        }
        for (list<Wall*>::iterator wallIt = walls.begin(); wallIt != walls.end(); wallIt++)
        {
            collisionQueue.push({(*wallIt)->timeToCollision(*ballIt), *wallIt, *ballIt});
        }
        collisionQueue.push({paddle.timeToCollision(*ballIt), &paddle, *ballIt});
    }
}

void PlayStateModel::removeDeletedObjects()
{
    // Remove every balls that got deleted 
    balls.remove_if([](Ball* ball) { 
        bool shouldRemove = ball->isDeleted;
        if (shouldRemove) {
            delete ball; // Free the memory allocated for the deleted ball
        }
        return shouldRemove;
    });

    // Remove every buffs that got deleted 
    buffs.remove_if([](Ball* buff) { 
        bool shouldRemove = buff->isDeleted;
        if (shouldRemove) {
            delete buff; // Free the memory allocated for the deleted buff
        }
        return shouldRemove;
    });
    
    // Remove and increased game points for every brick that is deleted
    int newPoints = 0;
    bricks.remove_if([&newPoints](Brick* brick) {
        if (brick->isDeleted) {
            newPoints += brick->brickPoint;
            delete brick; //Free the memory allocated for the deleted brick
            return true;
        }
        return false;
    });
    gamePoint += newPoints;
    gameScore.setString("Score: " + to_string(gamePoint));
}

void PlayStateModel::updateObjects(float deltaTime)
{
    // Update movement of balls, buffs and paddle
    for (list<Ball*>::iterator ballIt = balls.begin(); ballIt != balls.end(); ++ballIt)
    {
        (*ballIt)->updateMovement(deltaTime);
    }
        for (list<Ball*>::iterator buffIt = buffs.begin(); buffIt != buffs.end(); ++buffIt)
    {
        (*buffIt)->updateMovement(deltaTime);
    }
    paddle.updateMovement(deltaTime);
}

void PlayStateModel::addBall(Ball* ball)
{
    balls.push_back(ball);
}

void PlayStateModel::addBuff(Ball* buff)
{
    buffs.push_back(buff);
}

void PlayStateModel::addEvent(CollisionEvent event)
{
    collisionQueue.push(event);
}

std::list <Brick*> PlayStateModel::getLayout(int mapLayout[], int width, int height)
{
    std::list <Brick*> bricks;
    for (int r = 0; r < height; r++)
    {
        for (int c = 0; c < width; c++)
        {
            if (mapLayout[r * width + c] == 0) continue;
            bricks.push_back(new Brick(mapLayout[r * width + c], 1, sf::Vector2f(30 + 60 * c, 30 + 30 * r), this));
        }
    }
    return bricks;
}