#pragma once

#include <SFML/Graphics.hpp>
#include "Ball.hpp"

class PlayStateModel;

class Brick: public Collider
{
public:
    int brickPoint;
    sf::RectangleShape body;
    bool isDeleted = false;

    Brick(int brickType, int buffType, sf::Vector2f postition, PlayStateModel* model);
    // Handle collision with ball;
    void collideWith(Ball* ball) override; 

    // Calculate time at collision
    float timeToCollision(Ball* ball) override;

    bool getIsDeleted() const override { return isDeleted; }

private:
    int brickType;
    int buffType;

    PlayStateModel* model;
};
