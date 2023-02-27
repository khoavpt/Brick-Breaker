#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

#include "paddle.h"
#include "ball.h"

int MAP_LAYOUT[100] =  {0, 2, 2, 2, 3, 3, 2, 2, 2, 0,
                        0, 2, 2, 2, 1, 1, 2, 2, 2, 0,
                        0, 2, 2, 2, 1, 1, 2, 2, 2, 0,
                        0, 2, 2, 2, 3, 3, 2, 2, 2, 0,
                        0, 0, 2, 2, 3, 3, 2, 2, 0, 0,
                        0, 0, 0, 1, 1, 1, 1, 0, 0, 0,
                        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                        0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

int main()
{
    sf::RenderWindow window(sf::VideoMode(600.0f, 800.0f), "Many Brick Breaker", sf::Style::Close);
    sf::Clock clock;


    Paddle paddle(250.0f);
    Ball ball(sf::Vector2f(300.0f, 400.0f));
    vector <Brick> bricks = getLayout(MAP_LAYOUT, 10, 10);

    float deltaTime = 0.0f;

    while(window.isOpen())
    {
        deltaTime = clock.restart().asSeconds();
        if (deltaTime > 1.0f / 20.0f) deltaTime = 1.0f / 20.f;

        sf::Event event;
        while(window.pollEvent(event))
        {
            if (event.type == event.Closed) window.close();
        }

        // Update paddle and ball movements
        paddle.updateMovement(deltaTime);
        ball.updateMovement(deltaTime, paddle.body, bricks);
        
        window.clear(sf::Color(0, 0, 204, 255));

        window.draw(paddle.body);
        window.draw(ball.body);
        for (int i = 0; i < int(bricks.size()); i++)
        {
            window.draw(bricks[i].body);
        }
        window.display();
    }
    return 0;
}