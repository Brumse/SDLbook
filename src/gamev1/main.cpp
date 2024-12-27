
#include <memory>
#include "game.h"
#include <iostream>


int main(int argc, char const *argv[])
{
    auto g_game = Game::instance();
    if(!g_game->init("Chapter 1",100,100,640,480,false)){
        std::cout << "game init failure - "<<SDL_GetError()<<std::endl; 
        return EXIT_FAILURE;
    }

    while(g_game->running())
    {
        
        g_game->handleEvents();
        g_game->update();
        g_game->render();
        SDL_Delay(10);
    }
    
    std::cout<< "Game closing.."<<std::endl;
    g_game->clean();

    return EXIT_SUCCESS;
}
