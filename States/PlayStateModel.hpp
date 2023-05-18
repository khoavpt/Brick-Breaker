#pragma once
#include <list>
#include <queue>

#include "State.hpp"
#include "../Game.hpp"
#include "../Objects/Paddle.hpp"
#include "../Objects/Bricks.hpp"
#include "../Objects/Wall.hpp"
#include "../CollisionEvent.hpp"

class PlayStateModel
{
public:
    PlayStateModel(int level);
    ~PlayStateModel();

    list <Brick*> bricks;
    list <Ball*> balls;
    list <Ball*> buffs;
    list <Wall*> walls;
    priority_queue<CollisionEvent> collisionQueue; // Contain all future collisions that would occur
    Paddle paddle;
    int gamePoint;
    int level;
    float currentTime = 0.0f;

    void removeDeletedObjects();
    void updateObjects(float deltaTime);
    void addBall(Ball* newBall); // Add new ball
    void doubleBalls(); // Double the balls
    void addBuff(Ball* newBuff); // Add new buff
    void addEvent(CollisionEvent event);
private:
    std::list <Brick*> getLayout(int levelNumber);
    void recalculateCollisionQueue();
};
