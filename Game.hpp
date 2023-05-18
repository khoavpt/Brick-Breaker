#pragma once
#include <SFML/Graphics.hpp>
#include <stack>

class State;

class Game
{
    public:
        sf::RenderWindow window;

        Game();
        ~Game();

        void pushState(State* state);
        void popState();
        State* getActiveState();
        void gameLoop();
    
    private:
        std::stack <State*> states;
        
        void loadBackgroundImage();
        sf::Texture backgroundTexture;
        sf::Sprite backgroundSprite;
};