#include <SFML\Graphics.hpp>
#include <vector>

#include "bricks.hpp"

Brick::Brick(int type, sf::Vector2f postition)
{
    this->type = type;
    body.setPosition(postition);
    body.setSize(sf::Vector2f(50.0f, 20.0f));
    body.setOrigin(body.getSize() / 2.0f);
    body.setOutlineThickness(2.0f);
    body.setOutlineColor(sf::Color::Black);
    if (type == 3) body.setFillColor(sf::Color::Red);
    else if(type == 2) body.setFillColor(sf::Color::Green);
    else body.setFillColor(sf::Color{160, 160, 160, 255});
}


std::vector <Brick> getLayout(int mapLayout[], int width, int height)
{
    std::vector <Brick> bricks;
    for (int r = 0; r < height; r++)
    {
        for (int c = 0; c < width; c++)
        {
            if (mapLayout[r * width + c] == 0) continue;
            bricks.push_back(Brick(mapLayout[r * width + c], sf::Vector2f(30 + 60 * c, 30 + 30 * r)));
        }
    }
    return bricks;
}


