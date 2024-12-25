
#include <memory>
#include "game.h"
#include <iostream>




std::unique_ptr<Game> g_game;


int main(int argc, char const *argv[])
{
    g_game = std::make_unique<Game>();
    if(!g_game->init("Chapter 1",100,100,640,480,false)){
        std::cout << "init failure"<<std::endl; 
        return EXIT_FAILURE;
    }

    while(g_game->running())
    {
        g_game->handleEvents();
        g_game->update();
        g_game->render();
    }
    g_game->clean();


    return EXIT_SUCCESS;
}
