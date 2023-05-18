#pragma once
#include <queue>
#include "Objects/Ball.hpp"

class CollisionEvent
{
public:
    float time;
    Collider* a;
    Ball* b;
    CollisionEvent(float time, Collider* a, Ball* b);
    void handleEvent(priority_queue<CollisionEvent> &collisionQueue, float currentTime);
    
    bool operator<(CollisionEvent other) const {
        return time > other.time;
    }
};