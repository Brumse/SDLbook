#include "inputhandler.h"
#include <iostream>
#include "game.h"

InputHandler *InputHandler::m_pInstance = nullptr;

InputHandler *InputHandler::Instance()
{
    if (m_pInstance == 0)
    {
        m_pInstance = new InputHandler();
    }
    return m_pInstance;
}

void InputHandler::initialiseJoysticks()
{

    if (SDL_WasInit(SDL_INIT_JOYSTICK) == 0)
    {
        SDL_InitSubSystem(SDL_INIT_JOYSTICK);
    }
    if (SDL_NumJoysticks() > 0)
    {
        for (int i = 0; i < SDL_NumJoysticks(); i++)
        {
            SDL_Joystick *joy = SDL_JoystickOpen(i);
            if (joy) // replaced: if(SDL_JoystickOpened(i)==1)
            {
                m_joysticks.push_back(joy);
            }
            else
            {
                std::cout << SDL_GetError();
            }
        }
        SDL_JoystickEventState(SDL_ENABLE);
        m_bJoysticksInitialised = true;

        std::cout << "Initialised" << m_joysticks.size() << " joystick(s)" << std::endl;
    }
    else
    {
        m_bJoysticksInitialised = false;
    }
}

void InputHandler::clean()
{
    if (m_bJoysticksInitialised)
    {
        for (unsigned int i = 0; i < SDL_NumJoysticks(); i++)
        {
            SDL_JoystickClose(m_joysticks[i]);
        }
    }
}

void InputHandler::update()
{
    SDL_Event event;
    auto g_game = Game::instance();
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            g_game->clean();
        }
    }
}