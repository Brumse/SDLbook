#include "game.h"
#include <iostream>

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
    SDL_SetRenderDrawColor(m_pRenderer, 255, 255, 255, 255);

    SDL_Surface *pTempSurface = SDL_LoadBMP("assets/rider.bmp");
    m_pTexture = SDL_CreateTextureFromSurface(m_pRenderer, pTempSurface);
    SDL_FreeSurface(pTempSurface);
    SDL_QueryTexture(m_pTexture, NULL, NULL, &m_sourceRectangle.w, &m_sourceRectangle.h);

    m_sourceRectangle.w=50;
    m_sourceRectangle.h=50;    
    m_sourceRectangle.x = 0;
    m_sourceRectangle.y = 0;

    m_destinationRectangle.x = 100;
    m_destinationRectangle.y = 100;
    m_destinationRectangle.w = m_sourceRectangle.w;
    m_destinationRectangle.h = m_sourceRectangle.h;

    m_bRunning = true;
    return true;
}

void Game::render()
{
    SDL_RenderClear(m_pRenderer);
    SDL_RenderCopy(m_pRenderer, m_pTexture, 0,0);
    SDL_RenderPresent(m_pRenderer);
}

void Game::clean()
{
    std::cout << "cleaning game" << std::endl;
    SDL_DestroyWindow(m_pWindow);
    SDL_DestroyRenderer(m_pRenderer);
    SDL_Quit();
}

void Game::handleEvents()
{
    SDL_Event event;
    if (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            m_bRunning = false;
            break;
        default:
            break;
        }
    }
}
void Game::update() {}
