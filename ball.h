#include <SFML\Graphics.hpp>
#include <iostream>
#include <vector>
#include <cmath>

#include "bricks.h"

using namespace std;

sf::Vector2f getReflectionVector(sf::Vector2f incomingVector, sf::Vector2f axis)
// Accept an incoming vector and an axis vector as inputs, return the reflected vector
{
    float temp = 2 * (incomingVector.x * axis.x + incomingVector.y * axis.y) / (axis.x * axis.x + axis.y * axis.y);
    return sf::Vector2f(temp * axis.x - incomingVector.x, temp * axis.y - incomingVector.y);
}

class Ball
{
    public:
        sf::CircleShape body;
        int point = 0;

    Ball(sf::Vector2f position)
    {
        velocity.x = 0.0f;
        velocity.y = 400.0f;
        body.setRadius(10.0f);
        body.setOrigin(10.0f, 10.0f);
        body.setPosition(position);
        body.setFillColor(sf::Color::White);
    }

    // Check for collision between the ball and the walls
    void checkCollisionWithWall()
    {
        sf::Vector2f origin = body.getPosition();

        // If the ball collided with the top or bottom wall, reflect velocity.y
        if (origin.y < 10.0f || origin.y > 790.0f)
        {
            velocity.y = -velocity.y;
        }

        // If the ball collided with side walls, reflect velocity.x
        if (origin.x < 10.0f || origin.x > 590.0f)
        {
            velocity.x = -velocity.x;
        }
    }

    // Check for collision between the ball and the paddle
    void checkCollisionWithPaddle(sf::RectangleShape paddle)
    {
        sf::Vector2f ballPosition = body.getPosition();
        float ballRadius = body.getRadius();
        sf::Vector2f paddlePosition = paddle.getPosition();
        sf::Vector2f paddleHalfSize = paddle.getSize() / 2.0f;
        
        float deltaY = ballPosition.y - paddlePosition.y;
        float deltaX = ballPosition.x - paddlePosition.x;
        if (deltaY + ballRadius + paddleHalfSize.y > 0.0f && deltaY < 0.0f &&  deltaX < paddleHalfSize.x + ballRadius && deltaX + ballRadius + paddleHalfSize.x > 0.0f)
        {

            // The reflected direction of the ball depends on what part of the paddle it hits.
            // Every part of the paddle will contain a different axis vector, the reflected direction will be the result of reflecting the incoming vector off that axis vector
            float deltaToHalfsizeRatio = deltaX / (paddleHalfSize.x + ballRadius);
            velocity = - velocity;
            velocity = getReflectionVector(velocity, sf::Vector2f(deltaToHalfsizeRatio, -4));
        }
        
    }

    // Check for collision between the ball and the bricks
    void checkCollisionWithBricks(vector <Brick> &bricks)
    {
        sf::Vector2f ballPosition = body.getPosition();
        float ballRadius = body.getRadius();
        for (int i = 0; i < int(bricks.size()); i++)
        {
            sf::Vector2f brickPosition = bricks[i].body.getPosition();
            sf::Vector2f brickHalfSize = bricks[i].body.getSize() / 2.0f;
            
            float deltaY = abs(brickPosition.y - ballPosition.y);
            float deltaX = abs(brickPosition.x - ballPosition.x);
            if (deltaY < ballRadius + brickHalfSize.y &&  deltaX < brickHalfSize.x + ballRadius)
            {
                // If the ball hit the top or bottom of a brick, reflect velocity.y
                if (deltaY > brickHalfSize.y)
                {
                    velocity.y = -velocity.y;
                }
                // If the ball hit the side of a brick, reflect velocity.x
                else if (deltaX > brickHalfSize.x)
                {
                    velocity.x = - velocity.x;
                }

                if (bricks[i].type == 3)
                {
                    point += 10;
                    bricks.erase(bricks.begin() + i);
                }
                else if (bricks[i].type == 2)
                {
                    point += 5;
                    bricks.erase(bricks.begin() + i);
                }
            }
        }
    }
    

    void updateMovement(float deltaTime, sf::RectangleShape paddleBody, vector <Brick> &bricks)
    { 
        checkCollisionWithWall();
        checkCollisionWithPaddle(paddleBody);
        checkCollisionWithBricks(bricks);
        body.move(velocity * deltaTime);
    }

    private:
        sf::Vector2f velocity;
        float speed;
};

