#include "CollisionEvent.hpp"
#include <iostream>

CollisionEvent::CollisionEvent(float time, Collider* a, Ball* b)
{
    this->time = time;
    this->a = a;
    this->b = b;
}

void CollisionEvent::handleEvent(priority_queue<CollisionEvent> &collisionQueue, float currentTime)
{
    // Let a collide with b
    a->collideWith(b);

    // Find all collision events involving collider a or ball b and update the time at collision
    priority_queue<CollisionEvent> updateQueue;
    while(!collisionQueue.empty())
    {
        CollisionEvent top = collisionQueue.top();
        collisionQueue.pop();
        if (top.a == a || top.b == a)
        {
            if (a->getIsDeleted()) continue;
            top.time = top.a->timeToCollision(top.b) + currentTime;
        }
        if (top.b == b || top.a == b)
        {
            if (b->getIsDeleted()) continue;
            top.time = top.a->timeToCollision(top.b) + currentTime;
        }
        updateQueue.push(top);
    }
    collisionQueue = updateQueue;
}