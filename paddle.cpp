
#include <SFML\Graphics.hpp>
#include <cmath>

#include "paddle.hpp"

Paddle::Paddle()
{
    this->speed = 300.0f;
    body.setSize(sf::Vector2f(100.0f, 15.0f));
    body.setOrigin(body.getSize() / 2.0f);
    body.setPosition(sf::Vector2f(300.0f, 740.0f));
    body.setFillColor(sf::Color::White);
    body.setOutlineThickness(2.0f);
    body.setOutlineColor(sf::Color::Black);
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
