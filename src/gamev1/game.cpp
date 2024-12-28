#include "game.h"
#include <iostream>
#include <algorithm>
#include "inputhandler.h"

Game *Game::s_pInstance = 0;

bool Game::init(const char *title, int xpos, int ypos, int width,
                int height, bool fullscreen)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        std::cout << "SDL init fail" << std::endl;
        return false;
    }
    std::cout << "SDL init Success" << std::endl;

    int fullscreenflag = fullscreen ? static_cast<int>(SDL_WINDOW_FULLSCREEN) : 0;
    m_pWindow = SDL_CreateWindow(title, xpos, ypos, width, height, fullscreenflag);

    if (m_pWindow == NULL)
    {
        std::cout << "window init fail" << std::endl;
        return false;
    }
    std::cout << "window creation success" << std::endl;
    m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);

    if (m_pRenderer == NULL)
    {
        std::cout << "renderer init fail" << std::endl;
        return false;
    }
    std::cout << "renderer creation success" << std::endl;
    SDL_SetRenderDrawColor(m_pRenderer, 255, 0, 0, 255);

    TextureManager::Instance()->load("assets/animate-alpha.png", "animate", m_pRenderer);

    m_gameObjects.push_back(new Player(new LoaderParams(100, 100, 128, 82, "animate")));
    m_gameObjects.push_back(new Enemy(new LoaderParams(300, 300, 128, 82, "animate")));

    auto i_inputHandler = InputHandler::Instance();
    i_inputHandler->initialiseJoysticks();

    m_bRunning = true;
    return true;
}

void Game::render()
{
    SDL_RenderClear(m_pRenderer);
    for (auto &go : m_gameObjects)
    {
        go->draw();
    }
    SDL_RenderPresent(m_pRenderer);
}

void Game::clean()
{
    std::cout << "cleaning game" << std::endl;
    SDL_DestroyWindow(m_pWindow);
    SDL_DestroyRenderer(m_pRenderer);
    auto i_inputHandler = InputHandler::Instance();
    i_inputHandler->clean();
    SDL_Quit();
}

void Game::handleEvents()
{
    auto i_inputHandler = InputHandler::Instance();
    i_inputHandler->update(); 
}

void Game::update()
{
    std::for_each(m_gameObjects.begin(), m_gameObjects.end(), [](auto &go)
                  { go->update(); });
}

Game *Game::instance()
{
    if (s_pInstance == nullptr)
    {
        s_pInstance = new Game();
        return s_pInstance;
    }
    return s_pInstance;
}
