#include <SFML\Graphics.hpp>
#include <iostream>
#include <vector>
#include <cmath>

#include "Ball.hpp"

using namespace std;

sf::Vector2f getReflectionVector(sf::Vector2f incomingVector, sf::Vector2f axis)
// Accept an incoming vector and an axis vector as inputs, return the reflected vector
{
    float temp = 2 * (incomingVector.x * axis.x + incomingVector.y * axis.y) / (axis.x * axis.x + axis.y * axis.y);
    return sf::Vector2f(temp * axis.x - incomingVector.x, temp * axis.y - incomingVector.y);
}

Ball::Ball(sf::Vector2f position)
{
    velocity.x = 0.0f;
    velocity.y = 400.0f;
    body.setRadius(10.0f);
    body.setOrigin(10.0f, 10.0f);
    body.setPosition(position);
    body.setOutlineColor(sf::Color::Black);
}

// Check for collision between the ball and the walls
void Ball::checkCollisionWithWall()
{
    sf::Vector2f origin = body.getPosition();

    // If the ball collided with the top wall, reflect velocity.y
    if (origin.y < 0.0f)
    {
        velocity.y = -velocity.y;
    }

    // If the ball collided with side walls, reflect velocity.x
    if (origin.x < 10.0f || origin.x > 590.0f)
    {
        velocity.x = -velocity.x;
    }

    // Remove the ball if it reachs the bottom
    if (origin.y > 800.0f) isRemoved = true;
}

// Check for collision between the ball and the paddle
void Ball::checkCollisionWithPaddle(sf::RectangleShape paddle, bool &canCollide)
{
    sf::Vector2f ballPosition = body.getPosition();
    float ballRadius = body.getRadius();
    sf::Vector2f paddlePosition = paddle.getPosition();
    sf::Vector2f paddleHalfSize = paddle.getSize() / 2.0f;
    
    float deltaY = paddlePosition.y - ballPosition.y;
    float deltaX = paddlePosition.x - ballPosition.x;
    float intersectX = abs(deltaX) - ballRadius - paddleHalfSize.x;
    float intersectY = abs(deltaY) - ballRadius - paddleHalfSize.y;
    if (intersectX < 0.0f && intersectY < 0.0f)
    {
        if (intersectX <= intersectY)
        {
            if (deltaY > 0.0f)
            {
                body.move(0.0f, intersectY);
            }
            else
            {
                body.move(0.0f, -intersectY);
            }
            // The reflected direction of the ball depends on what part of the paddle it hits.
            // Every part of the paddle will contain a different axis vector, the reflected direction will be the result of reflecting the incoming vector off that axis vector
            velocity = - velocity;
            float deltaToHalfsizeRatio = deltaX / (paddleHalfSize.x + ballRadius);
            velocity = getReflectionVector(velocity, sf::Vector2f(deltaToHalfsizeRatio, 3));
        }
        else if (intersectX > intersectY)
        {
            velocity.x = - velocity.x;
            if (deltaX > 0.0f)
            {
                body.move(intersectX , 0.0f);
            }
            else
            {
                body.move(-intersectX , 0.0f);
            }
        }
    }        
}

// Check for collision between the ball and the bricks
void Ball::checkCollisionWithBricks(vector <Brick> &bricks, bool &canCollide, int &gamePoint)
{
    sf::Vector2f ballPosition = body.getPosition();
    float ballRadius = body.getRadius();
    for (int i = 0; i < int(bricks.size()); i++)
    {
        sf::Vector2f brickPosition = bricks[i].body.getPosition();
        sf::Vector2f brickHalfSize = bricks[i].body.getSize() / 2.0f;
        
        float deltaY = brickPosition.y - ballPosition.y;
        float deltaX = brickPosition.x - ballPosition.x;
        float intersectX = abs(deltaX) - ballRadius - brickHalfSize.x;
        float intersectY = abs(deltaY) - ballRadius - brickHalfSize.y;
        if (intersectX < 0.0f && intersectY < 0.0f)
        {
            // If the ball hit the top or bottom of a brick, reflect velocity.y
            if (intersectX <= intersectY && canCollide)
            {
                if (deltaY > 0.0f)
                {
                    body.move(0.0f, intersectY);
                }
                else
                {
                    body.move(0.0f, -intersectY);
                }
                velocity.y = - velocity.y;
            }
            // If the ball hit the side of a brick, reflect velocity.x
            else if (intersectX > intersectY && canCollide)
            {
                if (deltaX > 0.0f)
                {
                    body.move(intersectX , 0.0f);
                }
                else
                {
                    body.move(-intersectX , 0.0f);
                }
                velocity.x = - velocity.x;
            }
            canCollide = false;

            // Delete brick after collision
            if (bricks[i].type == 3)
            {
                gamePoint += 10;
                bricks.erase(bricks.begin() + i);
            }
            else if (bricks[i].type == 2)
            {
                gamePoint += 5;
                bricks.erase(bricks.begin() + i);
            }
        }
    }
}


void Ball::updateMovement(float deltaTime, sf::RectangleShape paddleBody, vector <Brick> &bricks, bool &canCollide, int &gamePoint)
{ 
    checkCollisionWithWall();
    checkCollisionWithPaddle(paddleBody, canCollide);
    checkCollisionWithBricks(bricks, canCollide, gamePoint);
    body.move(velocity * deltaTime);
}

