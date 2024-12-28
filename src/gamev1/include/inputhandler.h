#pragma once

#include "SDL.h"
#include <vector>

class InputHandler
{
public:
    static InputHandler *Instance();
    void update();
    void clean();
    void initialiseJoysticks();
    bool joystickInitialised()
    {
        return m_bJoysticksInitialised;
    }

private:
    InputHandler() {}
    ~InputHandler() {}

    static InputHandler *m_pInstance;
    std::vector<SDL_Joystick *> m_joysticks;
    bool m_bJoysticksInitialised;
};
