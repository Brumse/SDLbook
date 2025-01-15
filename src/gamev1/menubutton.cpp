#include "menubutton.h"
#include "vector2D.h"
#include "inputhandler.h"

MenuButton::MenuButton(const LoaderParams *pParams) : SDLGameObject(pParams)
{
    m_currentFrame = MOUSE_OUT;
}

void MenuButton::draw()
{
    SDLGameObject::draw();
}

void MenuButton::update()
{
    Vector2D *pMousePos = InputHandler::Instance()->getMousePosition();
}

void MenuButton::clean(){}

