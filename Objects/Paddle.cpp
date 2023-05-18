
#include <SFML\Graphics.hpp>
#include <cmath>
#include <iostream>

#include "Paddle.hpp"
#include "../States/PlayStateModel.hpp"
#include "../Constants.hpp"

sf::Vector2f getReflectionVector(sf::Vector2f incomingVector, sf::Vector2f axis)
// Accept an incoming vector and an axis vector as inputs, return the reflected vector
{
    float temp = 2 * (incomingVector.x * axis.x + incomingVector.y * axis.y) / (axis.x * axis.x + axis.y * axis.y);
    return sf::Vector2f(temp * axis.x - incomingVector.x, temp * axis.y - incomingVector.y);
}

Paddle::Paddle(PlayStateModel* model)
{
    this->speed = PADDLE_SPEED;
    this->model = model;
    this->size = (sf::Vector2f(PADDLE_WIDTH, PADDLE_HEIGHT));

    body.setSize(size);
    body.setOrigin(body.getSize() / 2.0f);
    body.setPosition(sf::Vector2f(BOARD_WIDTH / 2.0f, BOARD_HEIGHT * 7.0f / 8.0f));
    body.setFillColor(sf::Color::White);
    body.setOutlineThickness(2.0f);
    body.setOutlineColor(sf::Color::Black);
}

// Calculate time at collision
float Paddle::timeToCollision(Ball* ball)
{
    if (ball->velocity.y <= 0.0f) return INFINITY;
    else
    {
        sf::Vector2f ballPosition = ball->body.getPosition();
        sf::Vector2f paddlePosition = this->body.getPosition();
        float deltaX = paddlePosition.x - ballPosition.x;
        
        float distance = paddlePosition.y - ballPosition.y - BALL_RADIUS - this->size.y / 2;
        return (distance > 1.0f) ? distance / ball->velocity.y : INFINITY;
    }
}

// Handle collision with ball;
void Paddle::collideWith(Ball* ball)
{   
    // Get the ball postion
    sf::Vector2f ballPosition = ball->body.getPosition();
    
    // Get the paddle position
    sf::Vector2f paddlePosition = body.getPosition();

    // Calculate the intersection of the ball and paddle
    float deltaX = paddlePosition.x - ballPosition.x;

    if (abs(deltaX) < BALL_RADIUS + this->size.x / 2)
    {
        if (ball->buffType == 1) 
        {
            Ball* newBall = new Ball(body.getPosition() - sf::Vector2f(0.0f, 20.0f), sf::Vector2f(0.0f, -400.0f), 0);
            model->addBall(newBall);
            ball->isDeleted = true;
            return;
        }
        if (ball->buffType == 2)
        {
            ball->isDeleted = true;
            model->doubleBalls();
        }
        ball->velocity = - ball->velocity;
        float deltaToHalfsizeRatio = deltaX / (this->size.x / 2 + BALL_RADIUS);
        ball->velocity = getReflectionVector(ball->velocity, sf::Vector2f(deltaToHalfsizeRatio, 3));
    }
}

void Paddle::updateMovement(float deltaTime)
{
    sf::Vector2f paddlePosition = body.getPosition();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) && paddlePosition.x < 550.0f)
    {
        velocity.x += speed;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) && paddlePosition.x > 50.0f)
    {
        velocity.x -= speed;
    }
    body.move(velocity * deltaTime);
    velocity.x = 0.0f;
}
