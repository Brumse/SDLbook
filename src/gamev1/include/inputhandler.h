#pragma once

#include "SDL.h"
#include <vector>
#include <vector2D.h>
#include <utility>
#include <algorithm>

enum mouse_button
{
    LEFT = 0,
    MIDDLE = 1,
    RIGHT = 2
};

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

    bool getButtonState(int joy, int buttonNumber)
    {
        return m_buttonStates[joy][buttonNumber];
    }
    bool getMouseButtonState(int buttonNumber)
    {
        return m_mouseButtonStates[buttonNumber];
    }
    Vector2D *getMousePosition()
    {
        return m_mousePosition;
    }
    bool isKeyDown(SDL_Scancode key);

private:
    InputHandler() : m_mouseButtonStates(3, false), m_mousePosition(new Vector2D(0.0, 0.0)) {}
    ~InputHandler()
    {
        std::for_each(m_joyStickValues.begin(), m_joyStickValues.end(), [](auto &p)
                      {
            delete p.first;
            delete p.second; });
        delete m_mousePosition;
    }
    // JOYSTICK/CONTROLLER
    std::vector<SDL_Joystick *> m_joysticks;
    std::vector<std::pair<Vector2D *, Vector2D *>> m_joyStickValues;
    static InputHandler *m_pInstance;
    bool m_bJoysticksInitialised;
    const int m_joystickDeadZone = 10000;
    std::vector<std::vector<bool>> m_buttonStates;

    // MOUSE
    Vector2D *m_mousePosition;
    std::vector<bool> m_mouseButtonStates;

    // KEYBOARD
    const Uint8 *m_keystate;

    // handle keyboard events
    void onKeyDown();
    void onKeyUp();

    // handle mouse events
    void onMouseMove(SDL_Event &event);
    void onMouseButtonDown(SDL_Event &event);
    void onMouseButtonUp(SDL_Event &event);

    // handle joysticks events
    void onJoystickAisMove(SDL_Event &event);
    void onJoystickButtonDown(SDL_Event &event);
    void onJoystickButtonUp(SDL_Event &event);
};
