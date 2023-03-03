#pragma once
#include <SFML\Graphics.hpp>

class Brick
{
    public:
        sf::RectangleShape body;
        int type;

    Brick(int type, sf::Vector2f postition);
};

std::vector <Brick> getLayout(int mapLayout[], int width, int height);
