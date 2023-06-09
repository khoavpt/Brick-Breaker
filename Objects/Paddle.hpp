#pragma once

#include "Ball.hpp"

class PlayStateModel;

class Paddle: public Collider
{
public:
    sf::RectangleShape body;

    Paddle(PlayStateModel* model);
    void updateMovement(float deltaTime);

    // Handle collision with ball;
    void collideWith(Ball* ball) override; 

    // Calculate time at collision
    float timeToCollision(Ball* ball) override;

    bool getIsDeleted() const override { return isDeleted; }

private:
    sf::Vector2f velocity;
    sf::Vector2f size;
    float speed;
    PlayStateModel* model;
};