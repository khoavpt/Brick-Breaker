#include <SFML\Graphics.hpp>
#include <cmath>

class Paddle
{
    public:
        sf::RectangleShape body;

    Paddle(float speed)
    {
        this->speed = speed;
        body.setSize(sf::Vector2f(100.0f, 20.0f));
        body.setOrigin(body.getSize() / 2.0f);
        body.setPosition(sf::Vector2f(300.0f, 740.0f));
        body.setFillColor(sf::Color::White);
        body.setOutlineThickness(2.0f);
        body.setOutlineColor(sf::Color::Black);
    }

    void updateMovement(float deltaTime)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
        {
            velocity.x += speed;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
        {
            velocity.x -= speed;
        }
        body.move(velocity * deltaTime);
        velocity.x = 0.0f;
    }

    private:
        sf::Vector2f velocity;
        float speed;
};