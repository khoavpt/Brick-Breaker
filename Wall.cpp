#include <SFML\Graphics.hpp>
#include <cmath>
#include <iostream>

#include "Wall.hpp"
#include "Constants.hpp"

Wall::Wall(int type)
{
    this->type = type;
}

// Calculate time to collision
float Wall::timeToCollision(Ball* ball)
{
    sf::Vector2f ballPosition = ball->body.getPosition();
    float time;
    if (type == 0)
    {
        if((BALL_RADIUS - ballPosition.x) > 0) return INFINITY;
        time = (BALL_RADIUS - ballPosition.x) / ball->velocity.x;
    }
    else if (type == 1)
    {
        if((BOARD_WIDTH - BALL_RADIUS - ballPosition.x) < 0) return INFINITY;
        time = (BOARD_WIDTH - BALL_RADIUS - ballPosition.x) / ball->velocity.x;
    }
    else if (type == 2)
    {
        if((BALL_RADIUS - ballPosition.y) > 0) return INFINITY;
        time = (BALL_RADIUS - ballPosition.y ) / ball->velocity.y;
    }
    else 
    {
        if ((BOARD_HEIGHT + BALL_RADIUS - ballPosition.y ) < 0) return INFINITY;
        time = (BOARD_HEIGHT + BALL_RADIUS - ballPosition.y ) / ball->velocity.y;
    }
    
    if (time > 0.0) return time;
    return INFINITY;
}

void Wall::collideWith(Ball* ball)                       
{
    if (type == 0 || type == 1) ball->velocity.x = -ball->velocity.x;
    else if (type == 2) ball->velocity.y = -ball->velocity.y;
    else ball->isDeleted = true;
}