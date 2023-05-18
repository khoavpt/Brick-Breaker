#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

#include "PlayStateModel.hpp"
#include "../Constants.hpp"

const float SQRT_2 = 1.414213;

PlayStateModel::PlayStateModel(int level):
    paddle(this)
{
    this->level = level;
    gamePoint = 0;

    balls = {new Ball(sf::Vector2f(300.0f, 500.0f), sf::Vector2f(BALL_ORGINAL_VELOCITY_X, BALL_ORGINAL_VELOCITY_Y), 0)};
    walls = {new Wall(0), new Wall(1), new Wall(2), new Wall(3)};
    bricks = getLayout(this->level);

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

PlayStateModel::~PlayStateModel()
{
    for (auto brick : bricks) {delete brick;}
    for (auto ball : balls) {delete ball;}
    for (auto buff : buffs) {delete buff;}
    for (auto wall : walls) {delete wall;}
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
    if(newPoints > 0)
    {
        gamePoint += newPoints;
    }
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
    for (list<Ball*>::iterator ballIt2 = balls.begin(); ballIt2 != balls.end(); ballIt2++)
    { 
        addEvent({currentTime + ball->timeToCollision(*ballIt2), ball, *ballIt2});
    }
    for (list<Brick*>::iterator brickIt = bricks.begin(); brickIt != bricks.end(); brickIt++)
    {
        addEvent({currentTime + (*brickIt)->timeToCollision(ball), *brickIt, ball});
    }
    for (list<Wall*>::iterator wallIt = walls.begin(); wallIt != walls.end(); wallIt++)
    {
        addEvent({currentTime + (*wallIt)->timeToCollision(ball), *wallIt, ball});
    }
    addEvent({currentTime + paddle.timeToCollision(ball), &(paddle), ball});
}

void PlayStateModel::doubleBalls()
{
    list<Ball*> ballsCopy = balls;
    for (list<Ball*>::iterator ballIt = ballsCopy.begin(); ballIt != ballsCopy.end(); ballIt++)
    { 
        sf::Vector2f currentVelocity = (*ballIt)->velocity;
        (*ballIt)->velocity = sf::Vector2f((currentVelocity.x + currentVelocity.y) / SQRT_2, (currentVelocity.y - currentVelocity.x) / SQRT_2);
        addBall(new Ball((*ballIt)->body.getPosition(), sf::Vector2f((currentVelocity.x - currentVelocity.y) / SQRT_2, (currentVelocity.y + currentVelocity.x) / SQRT_2), 0));
    }
    recalculateCollisionQueue();
}

void PlayStateModel::addBuff(Ball* buff)
{
    buffs.push_back(buff);
    addEvent({currentTime + paddle.timeToCollision(buff), &(paddle), buff});
}

void PlayStateModel::addEvent(CollisionEvent event)
{
    collisionQueue.push(event);
}

// Recalculate the collision time of every events inside the collision queue
void PlayStateModel::recalculateCollisionQueue()
{
    priority_queue<CollisionEvent> updateQueue;
    while(!collisionQueue.empty())
    {
        CollisionEvent top = collisionQueue.top();
        collisionQueue.pop();
        top.time = top.a->timeToCollision(top.b) + currentTime;
        updateQueue.push(top);
    }
    collisionQueue = updateQueue;
}

std::list<Brick*> PlayStateModel::getLayout(int levelNumber)
{
    std::list<Brick*> bricks;
    std::ifstream file("Levels/level" + std::to_string(levelNumber) + ".txt");
    std::vector<int> brickLayout;
    std::vector<int> buffLayout;

    int value;
    // Read brickLayout values
    for (int i = 0; i < 100; i++)
    {
        file >> value;
        brickLayout.push_back(value);
    }
    // Read buffLayout values
    for (int i = 0; i < 100; i++)
    {
        file >> value;
        buffLayout.push_back(value);
    }

    for (int r = 0; r < 10; r++)
    {
        for (int c = 0; c < 10; c++)
        {
            if (brickLayout[r * 10 + c] == 0) continue;
            bricks.push_back(new Brick(brickLayout[r * 10 + c], buffLayout[r * 10 + c] , sf::Vector2f(30 + 60 * c, 100 + 30 * r), this));
        }
    }
    return bricks;
}

