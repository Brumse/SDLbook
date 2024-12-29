#pragma once

#include "SDL.h"
#include <vector>
#include <vector2D.h>
#include <utility>

class InputHandler
{
public:
    static InputHandler *Instance();
    void update();
    void clean();
    void initialiseJoysticks();
    int xvalue(int joy, int stick);
    int yvalue(int joy, int stick);

    bool joystickInitialised()
    {
        return m_bJoysticksInitialised;
    }

    bool getButtonState(int joy, int buttonNnumber)
    {
        return m_buttonStates[joy][buttonNnumber];
    }

private:
    InputHandler() {}
    ~InputHandler() {}

    std::vector<SDL_Joystick *> m_joysticks;
    std::vector<std::pair<Vector2D *, Vector2D *>> m_joyStickValues;
    static InputHandler *m_pInstance;
    bool m_bJoysticksInitialised;
    const int m_joystickDeadZone = 10000;
    std::vector<std::vector<bool>> m_buttonStates;
};
