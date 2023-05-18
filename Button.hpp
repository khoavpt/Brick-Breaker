#pragma once
#include "SFML/Graphics.hpp"

class Button
{
public:
    Button(sf::Vector2f position, sf::Vector2f shape, std::string text, sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor, sf::Font* font, std::string pathToTexture = "");
    sf::RectangleShape body;
    void update(sf::Vector2f mousePosition);
    bool isPressed = false;

    void draw(sf::RenderWindow& window);

private:
    sf::Text buttonText;
    sf::Font* font;
    int buttonState;

    sf::Color idleColor;
    sf::Color hoverColor;
    sf::Color activeColor;

    sf::Sprite imageSprite;
    sf::Texture textureForImageSprite;
};
