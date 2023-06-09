#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
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

        sf::Music* currentMusic = nullptr;
        std::map<std::string, sf::Music*> stateMusic; // Contains preloaded music for each state
};