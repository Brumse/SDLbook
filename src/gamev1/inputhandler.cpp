#include "inputhandler.h"
#include <iostream>
#include "game.h"
#include <utility>
#include <vector>

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
                m_joyStickValues.push_back(std::make_pair(new Vector2D(0, 0), new Vector2D(0, 0)));
                std::vector<bool> tempButtons;

                for (int j = 0; j < SDL_JoystickNumButtons(joy); j++)
                {
                    tempButtons.push_back(false);
                }
                m_buttonStates.push_back(tempButtons);
            }
            else
            {
                std::cout << SDL_GetError();
            }
        }

        SDL_JoystickEventState(SDL_ENABLE);
        m_bJoysticksInitialised = true;

        std::cout << "Initialised " << m_joysticks.size() << " joystick(s)" << std::endl;
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
    
    SDL_QuitSubSystem(SDL_INIT_JOYSTICK);
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

        // Joystick moved
        if (event.type == SDL_JOYAXISMOTION)
        {
            int whichOne = event.jaxis.which;

            if (event.jaxis.axis == 0)
            {
                auto val = event.jaxis.value;
                if (val > m_joystickDeadZone)
                {
                    m_joyStickValues[whichOne].first->setX(1);
                }
                else if (val < (-m_joystickDeadZone))
                {
                    m_joyStickValues[whichOne].first->setX(-1);
                }
                else
                {
                    m_joyStickValues[whichOne].first->setX(0);
                }
            }
            if (event.jaxis.axis == 1)
            {
                std::cout << '\r' << std::string(80, ' ');
                std::cout << '\r' << event.jaxis.value << std::flush;

                if (event.jaxis.value > m_joystickDeadZone)
                {
                    m_joyStickValues[whichOne].first->setY(1);
                }
                else if (event.jaxis.value < -m_joystickDeadZone)
                {
                    m_joyStickValues[whichOne].first->setY(-1);
                }
                else
                {
                    m_joyStickValues[whichOne].first->setY(0);
                }
            }
            if (event.jaxis.axis == 3)
            {
                if (event.jaxis.value > m_joystickDeadZone)
                {
                    m_joyStickValues[whichOne].second->setX(1);
                }
                else if (event.jaxis.value < -m_joystickDeadZone)
                {
                    m_joyStickValues[whichOne].second->setX(-1);
                }
                else
                {
                    m_joyStickValues[whichOne].second->setX(0);
                }
            }
            if (event.jaxis.axis == 4)
            {
                if (event.jaxis.value > m_joystickDeadZone)
                {
                    m_joyStickValues[whichOne].second->setY(1);
                }
                else if (event.jaxis.value < -m_joystickDeadZone)
                {
                    m_joyStickValues[whichOne].second->setY(-1);
                }
                else
                {
                    m_joyStickValues[whichOne].second->setY(0);
                }
            }
        }
        if (event.type == SDL_JOYBUTTONDOWN)
        {
            int whichOne = event.jaxis.which;
            m_buttonStates[whichOne][event.jbutton.button] = true;
        }
        if (event.type == SDL_JOYBUTTONUP)
        {
            int whichOne = event.jaxis.which;
            m_buttonStates[whichOne][event.jbutton.button] = false;
        }
    }
}

int InputHandler::xvalue(int joy, int stick)
{
    if (m_joyStickValues.size() > 0)
    {
        if (stick == 1)
        {
            return m_joyStickValues[joy].first->getX();
        }
        else if (stick == 2)
        {
            return m_joyStickValues[joy].second->getX();
        }
    }
    return 0;
}

int InputHandler::yvalue(int joy, int stick)
{
    if (m_joyStickValues.size() > 0)
    {
        if (stick == 1)
        {
            return m_joyStickValues[joy].first->getY();
        }
        else if (stick == 2)
        {
            return m_joyStickValues[joy].second->getY();
        }
    }
    return 0;
}