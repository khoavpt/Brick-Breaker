#include "Button.hpp"

Button::Button(sf::Vector2f position, sf::Vector2f shape, std::string text, sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor, sf::Font* font, std::string pathToTexture)
{
    this->idleColor = idleColor;
    this->hoverColor = hoverColor;
    this->activeColor = activeColor;
    this->isPressed = false;

    body.setSize(shape);
    body.setOrigin(shape.x / 2.0f, shape.y / 2.0f);
    body.setPosition(position);
    body.setFillColor(this->idleColor);

    buttonText.setString(text);
    buttonText.setFont(*font);
    buttonText.setCharacterSize(30);
    sf::FloatRect textBounds = buttonText.getLocalBounds();
    buttonText.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);

    if (!pathToTexture.empty())
    {
        textureForImageSprite.loadFromFile(pathToTexture);
        buttonText.setPosition(position.x, position.y + shape.y * 0.4f);
        
        imageSprite.setTexture(textureForImageSprite);
        sf::Vector2f imageSize(shape * 0.75f);
        imageSprite.setScale(imageSize.x / textureForImageSprite.getSize().x, imageSize.y / textureForImageSprite.getSize().y);
        imageSprite.setOrigin(imageSprite.getLocalBounds().width / 2.0f, imageSprite.getLocalBounds().height / 2.0f);
        imageSprite.setPosition(position.x, position.y - shape.y * 0.1f);
    }
    else
    {
        buttonText.setPosition(position);
    }
}


void Button::update(sf::Vector2f mousePosition)
{
    this->isPressed = false;
    this->buttonState = 0;

    if (this->body.getGlobalBounds().contains(mousePosition))
    {
        this->buttonState = 1;
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) this->buttonState = 2;
    }

    if (this->buttonState == 0)
    {
        this->body.setFillColor(idleColor);
    }
    else if (this->buttonState == 1)
    {
        this->body.setFillColor(hoverColor);
    }
    else
    {
        this->body.setFillColor(activeColor);
        isPressed = true;
    }
}

void Button::draw(sf::RenderWindow& window)
{
    window.draw(body);
    window.draw(buttonText);

    if (imageSprite.getTexture() != nullptr)
    {
        window.draw(imageSprite);
    }
}