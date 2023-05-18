#include <SFML\Graphics.hpp>
#include <cmath>

#include "Bricks.hpp"
#include "../States/PlayStateModel.hpp"
#include "../Constants.hpp"

float divide(float a, float b)
{
    if (b == 0)
    {
        if (a >= 0) return INFINITY;
        if (a < 0) return -INFINITY;
    }
    return a / b;
}

Brick::Brick(int brickType, int buffType, sf::Vector2f postition, PlayStateModel* model)
{
    this->brickType = brickType;
    this->buffType = buffType;
    this->model = model;
    body.setPosition(postition);
    body.setSize(sf::Vector2f(BRICK_WIDTH, BRICK_HEIGHT));
    body.setOrigin(body.getSize() / 2.0f);
    body.setOutlineThickness(2.0f);
    body.setOutlineColor(sf::Color::Black);
    if (brickType == 3) {body.setFillColor(sf::Color::Red); brickPoint = 10;}
    else if(brickType == 2) {body.setFillColor(sf::Color::Green); brickPoint = 5;}
    else body.setFillColor(sf::Color{160, 160, 160, 255});
}

// Calculate time to collision
float Brick::timeToCollision(Ball* ball)
{
    // Get the brick position and halfSize
    sf::Vector2f brickHalfSize = sf::Vector2f(BRICK_WIDTH / 2.0f, BRICK_HEIGHT / 2.0f);
    sf::Vector2f brickPosition = body.getPosition();

    // Get the ball postion
    sf::Vector2f ballPosition = ball->body.getPosition();

    float deltaY = brickPosition.y - ballPosition.y;
    float deltaX = brickPosition.x - ballPosition.x;
    if (abs(deltaX) - BALL_RADIUS - brickHalfSize.x < 0.0 && abs(deltaY) - BALL_RADIUS - brickHalfSize.y < 0.0) return INFINITY;

    float constX = (deltaX >= 0) ? -BALL_RADIUS : BALL_RADIUS;
    float constY = (deltaY >= 0) ? -BALL_RADIUS : BALL_RADIUS;

    float t_x1 = divide(deltaX - brickHalfSize.x + constX, ball->velocity.x);
    float t_x2 = divide(deltaX + brickHalfSize.x + constX, ball->velocity.x);
    float t_y1 = divide(deltaY - brickHalfSize.y + constY, ball->velocity.y);
    float t_y2 = divide(deltaY + brickHalfSize.y + constY, ball->velocity.y);

    float xTime = (min(t_x1, t_x2) > 0.0) ? min(t_x1, t_x2) : max(t_x1, t_x2);
    float yTime = (min(t_y1, t_y2) > 0.0) ? min(t_y1, t_y2) : max(t_y1, t_y2);

    if (xTime < 0.0f || yTime < 0.0f) return INFINITY;
    if (abs(ballPosition.y + ball->velocity.y * xTime - brickPosition.y) >= brickHalfSize.y + BALL_RADIUS) xTime = INFINITY;
    if (abs(ballPosition.x + ball->velocity.x * yTime - brickPosition.x) >= brickHalfSize.x  + BALL_RADIUS) yTime = INFINITY;

    if (xTime < yTime)
    {
        return xTime;
    }
    else
    {
        return yTime;
    }
}

// Handle collision between brick and ball
void Brick::collideWith(Ball* ball)
{
    // Get the brick position and halfSize
    sf::Vector2f brickHalfSize = sf::Vector2f(BRICK_WIDTH / 2.0f, BRICK_HEIGHT / 2.0f);
    sf::Vector2f brickPosition = body.getPosition();

    // Get the ball postion
    sf::Vector2f ballPosition = ball->body.getPosition();

    float deltaY = brickPosition.y - ballPosition.y;
    float deltaX = brickPosition.x - ballPosition.x;

    float constX = (deltaX >= 0) ? -BALL_RADIUS : BALL_RADIUS;
    float constY = (deltaY >= 0) ? -BALL_RADIUS : BALL_RADIUS;

    float t_x1 = divide(deltaX - brickHalfSize.x + constX, ball->velocity.x);
    float t_x2 = divide(deltaX + brickHalfSize.x + constX, ball->velocity.x);
    float t_y1 = divide(deltaY - brickHalfSize.y + constY, ball->velocity.y);
    float t_y2 = divide(deltaY + brickHalfSize.y + constY, ball->velocity.y);

    float xTime = (min(t_x1, t_x2) > 0.0) ? min(t_x1, t_x2) : max(t_x1, t_x2);
    float yTime = (min(t_y1, t_y2) > 0.0) ? min(t_y1, t_y2) : max(t_y1, t_y2);

    if (yTime < xTime) ball->velocity.y = - ball->velocity.y;
    else ball->velocity.x = - ball->velocity.x;

    if (this->brickType == 2)
    {
        this->isDeleted = true;
    }
    else if (this->brickType == 3)
    {
        this->brickType = 2;
        this->body.setFillColor(sf::Color(153, 0, 0, 255));
    }

    if(buffType == 1) 
    {
        Ball* buff = new Ball(body.getPosition(), sf::Vector2f(BUFF_ORIGINAL_VELOCITY_X, BUFF_ORIGINAL_VELOCITY_Y), 1);
        model->addBuff(buff);
    }
    else if (buffType == 2)
    {
        Ball* buff = new Ball(body.getPosition(), sf::Vector2f(BUFF_ORIGINAL_VELOCITY_X, BUFF_ORIGINAL_VELOCITY_Y), 2);
        model->addBuff(buff);
    }
}


