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
    m_keystate = SDL_GetKeyboardState(0);

    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            g_game->clean();
            break;
        case SDL_JOYAXISMOTION:
            onJoystickAisMove(event);
            break;
        case SDL_JOYBUTTONDOWN:
            onJoystickButtonDown(event);
            break;
        case SDL_JOYBUTTONUP:
            onJoystickButtonUp(event);
            break;
        case SDL_MOUSEMOTION:
            onMouseMove(event);
            break;
        case SDL_MOUSEBUTTONDOWN:
            onMouseButtonDown(event);
            break;
        case SDL_MOUSEBUTTONUP:
            onMouseButtonUp(event);
            break;
        case SDL_KEYDOWN:
            onKeyDown();
            break;
        case SDL_KEYUP:
            onKeyUp();
            break;
        default:
            break;
        }
    }
}

bool InputHandler::isKeyDown(SDL_Scancode key)
{
    if (m_keystate != 0)
    {
        if (m_keystate[key] == 1)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    return false;
}
// KEYBOARDEVENTS
void InputHandler::onKeyDown() {}
void InputHandler::onKeyUp() {}

// MOUSE EVENTS
void InputHandler::onMouseMove(SDL_Event &event)
{
    m_mousePosition->setX(event.motion.x);
    m_mousePosition->setY(event.motion.y);
}
void InputHandler::onMouseButtonDown(SDL_Event &event)
{

    if (event.button.button == SDL_BUTTON_LEFT)
    {
        m_mouseButtonStates[LEFT] = true;
    }

    if (event.button.button == SDL_BUTTON_MIDDLE)
    {
        m_mouseButtonStates[MIDDLE] = true;
    }
    if (event.button.button == SDL_BUTTON_RIGHT)
    {
        m_mouseButtonStates[RIGHT] = true;
    }
}
void InputHandler::onMouseButtonUp(SDL_Event &event)
{
    if (event.button.button == SDL_BUTTON_LEFT)
    {
        m_mouseButtonStates[LEFT] = false;
    }

    if (event.button.button == SDL_BUTTON_MIDDLE)
    {
        m_mouseButtonStates[MIDDLE] = false;
    }
    if (event.button.button == SDL_BUTTON_RIGHT)
    {
        m_mouseButtonStates[RIGHT] = false;
    }
}

// JOTSTICK/CONTROLLER EVENTS
void InputHandler::onJoystickAisMove(SDL_Event &event)
{
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
}
void InputHandler::onJoystickButtonDown(SDL_Event &event)
{

    if (event.type == SDL_JOYBUTTONDOWN)
    {
        int whichOne = event.jaxis.which;
        m_buttonStates[whichOne][event.jbutton.button] = true;
    }
}
void InputHandler::onJoystickButtonUp(SDL_Event &event)
{
    if (event.type == SDL_JOYBUTTONUP)
    {
        int whichOne = event.jaxis.which;
        m_buttonStates[whichOne][event.jbutton.button] = false;
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
