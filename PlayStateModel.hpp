#pragma once
#include <list>
#include <queue>

#include "State.hpp"
#include "Game.hpp"
#include "Paddle.hpp"
#include "Bricks.hpp"
#include "Wall.hpp"

#include "CollisionEvent.hpp"

class PlayStateModel
{
public:
    PlayStateModel();

    list <Brick*> bricks;
    list <Ball*> balls;
    list <Ball*> buffs;
    list <Wall*> walls;
    priority_queue<CollisionEvent> collisionQueue; // Contain all future collisions that would occur
    Paddle paddle;
    int gamePoint;
    float currentTime = 0.0f;

    sf::Font font;
    sf::Text gameScore;
    void removeDeletedObjects();
    void updateObjects(float deltaTime);
    void addBall(Ball* newBall); // Add new ball
    void addBuff(Ball* newBuff); // Add new buff
    void addEvent(CollisionEvent event);
private:
    std::list <Brick*> getLayout(int mapLayout[], int width, int height);
};
