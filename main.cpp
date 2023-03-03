#include "game.hpp"
#include "MenuState.hpp"

int main()
{
    Game game;
    game.pushState(new MenuState(&game));
    game.gameLoop();
    return 0;
}