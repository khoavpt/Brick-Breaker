#pragma once
#include <SFML\Graphics.hpp>
#include "Collider.hpp"

using namespace std;

float dotProduct(sf::Vector2f v1, sf::Vector2f v2);

class PlayStateModel;

class Ball: public Collider
{
public:
    sf::CircleShape body;
    sf::Vector2f velocity;
    bool isDeleted = false;
    int buffType; // 0 if it's not a buff, 1 if it's a +1 buff

    Ball(sf::Vector2f position, sf::Vector2f velocity, int buffType);
    void updateMovement(float deltaTime);

    // Handle collision with ball;
    void collideWith(Ball* other) override; 

    // Calculate time at collision
    float timeToCollision(Ball* other) override;

    bool getIsDeleted() const override { return isDeleted; }
private:
    PlayStateModel* model;
};

