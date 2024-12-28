
#include <memory>
#include "game.h"
#include <iostream>

const int FPS = 60;
const int DELAY_TIME = 1000.0f / FPS;

int main(int argc, char const *argv[])
{
    Uint32 frameStart, frameTime;
    auto g_game = Game::instance();
    if (!g_game->init("Chapter 1", 100, 100, 640, 480, false))
    {
        std::cout << "game init failure - " << SDL_GetError() << std::endl;
        return EXIT_FAILURE;
    }

    while (g_game->running())
    {
        frameStart = SDL_GetTicks();

        g_game->handleEvents();
        g_game->update();
        g_game->render();

        frameTime = SDL_GetTicks() - frameStart;

        if (frameTime < DELAY_TIME)
        {
            SDL_Delay((int)(DELAY_TIME - frameTime));
        }
    }

    std::cout << "Game closing.." << std::endl;
    g_game->clean();

    return EXIT_SUCCESS;
}
