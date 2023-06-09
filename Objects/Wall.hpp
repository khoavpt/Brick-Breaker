#pragma once

#include "Ball.hpp"

class Wall: public Collider
{
public:
    int type; // 0 for left wall, 1 for right wall, 2 for top wall
    bool isDeleted = false;

    Wall(int type);

    // Handle collision with ball;
    void collideWith(Ball* ball) override; 

    // Calculate time at collision
    float timeToCollision(Ball* ball) override;

    bool getIsDeleted() const override { return isDeleted; }
};
