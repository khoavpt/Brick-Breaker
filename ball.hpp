#pragma once
#include <SFML\Graphics.hpp>

#include "Bricks.hpp"

using namespace std;

class Ball
{
    public:
        sf::CircleShape body;
        bool isRemoved = false;

    Ball(sf::Vector2f position);

    // Check for collision between the ball and the walls
    void checkCollisionWithWall();

    // Check for collision between the ball and the paddle
    void checkCollisionWithPaddle(sf::RectangleShape paddle, bool &canCollide);

    // Check for collision between the ball and the bricks
    void checkCollisionWithBricks(vector <Brick> &bricks, bool &canCollide, int &gamePoint);
    

    void updateMovement(float deltaTime, sf::RectangleShape paddleBody, vector <Brick> &bricks, bool &canCollide, int &gamePoint);

    private:
        sf::Vector2f velocity;
};

