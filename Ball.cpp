#include <SFML\Graphics.hpp>
#include <cmath>

#include "Ball.hpp"
#include "Constants.hpp"

using namespace std;

// Accept two vectors as inputs and return the dot product of them
float dotProduct(sf::Vector2f v1, sf::Vector2f v2)
{
    return v1.x * v2.x + v1.y * v2.y;
}

Ball::Ball(sf::Vector2f position, sf::Vector2f velocity, int buffType)
{
    this->velocity = velocity;
    this->buffType = buffType;
    if(buffType == 1) body.setFillColor(sf::Color::Red);
    
    body.setRadius(BALL_RADIUS);
    body.setOrigin(BALL_RADIUS, BALL_RADIUS);
    body.setPosition(position);
    body.setOutlineColor(sf::Color::Black);
}

// Calculate time at collision
float Ball::timeToCollision(Ball* other)
{
    sf::Vector2f delta_v(other->velocity.x - this->velocity.x, other->velocity.y - this->velocity.y);
    sf::Vector2f delta_r(other->body.getPosition().x - this->body.getPosition().x, other->body.getPosition().y - this->body.getPosition().y);
    float dotProduct_vr = dotProduct(delta_v, delta_r);
    float totalRadius = BALL_RADIUS + BALL_RADIUS;
    float delta = dotProduct_vr * dotProduct_vr - dotProduct(delta_v, delta_v) * (dotProduct(delta_r, delta_r) - totalRadius * totalRadius);
    if (dotProduct(delta_v, delta_r) >= 0 || delta < 0) return INFINITY;
    return  -(dotProduct_vr + sqrt(delta)) / dotProduct(delta_v, delta_v);
}

// Handle collision between two balls
void Ball::collideWith(Ball* other)
{
    sf::Vector2f delta_v(other->velocity.x - this->velocity.x, other->velocity.y - this->velocity.y);
    sf::Vector2f delta_r(other->body.getPosition().x - this->body.getPosition().x, other->body.getPosition().y - this->body.getPosition().y);
    float totalRadius = BALL_RADIUS + BALL_RADIUS;
    float j = dotProduct(delta_v, delta_r) / totalRadius;
    sf::Vector2f impulse(j * delta_r.x / totalRadius, j * delta_r.y / totalRadius);

    // Change the velocity of balls after collision
    this->velocity.x += impulse.x;
    this->velocity.y += impulse.y;
    other->velocity.x -= impulse.x;
    other->velocity.y -= impulse.y;
}

void Ball::updateMovement(float deltaTime)
{ 
    this->body.move(velocity * deltaTime);
}

