#pragma once
#include <SFML\Graphics.hpp>

class Paddle
{
    public:
        sf::RectangleShape body;

    Paddle();

    void updateMovement(float deltaTime);

    private:
        sf::Vector2f velocity;
        float speed;
};