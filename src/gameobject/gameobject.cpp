#include "gameobject.h"
#include <iostream>
#include "TextureManager.h"
#include "game.h"
#include "inputhandler.h"

// SDL GAME OBJECT
SDLGameObject::SDLGameObject(const LoaderParams *pParams) : GameObject(pParams), m_position(pParams->getX(), pParams->getY()), m_velocity(0, 0), m_acceleration(0, 0)
{
    m_width = pParams->getWidth();
    m_height = pParams->getHeight();
    m_textureID = pParams->getTextureID();

    m_currentRow = 1;
    m_currentFrame = 1;
}
void SDLGameObject::draw()
{
    TextureManager::Instance()->drawFrame(m_textureID, (int)m_position.getX(), (int)m_position.getY(), m_width, m_height, m_currentRow, m_currentFrame, Game::instance()->getRenderer());
}

void SDLGameObject::update()
{
    // m_velocity += m_acceleration;
    m_position += m_velocity;
}

void SDLGameObject::clean()
{
}

// PLAYER

Player::Player(const LoaderParams *pParmas) : SDLGameObject(pParmas)
{
}
void Player::draw()
{
    SDLGameObject::draw();
}
void Player::update()
{
    m_velocity.setX(0);
    m_velocity.setY(0);
    handleInput();
    m_currentFrame = int((SDL_GetTicks() / 100 % 6));
    SDLGameObject::update();
}
void Player::clean()
{
}

void Player::handleInput()
{
    auto i_inputHandler = InputHandler::Instance();
    if (i_inputHandler->joystickInitialised())
    {
        if (i_inputHandler->xvalue(0, 1) > 0 || i_inputHandler->xvalue(0, 1) < 0)
        {
            m_velocity.setX(1 * i_inputHandler->xvalue(0, 1));
        }
        if (i_inputHandler->yvalue(0, 1) > 0 || i_inputHandler->yvalue(0, 1) < 0)
        {
            m_velocity.setY(1 * i_inputHandler->yvalue(0, 1));
        }
        if (i_inputHandler->xvalue(0, 2) > 0 || i_inputHandler->xvalue(0, 2) < 0)
        {
            m_velocity.setX(1 * i_inputHandler->xvalue(0, 2));
        }
        if (i_inputHandler->yvalue(0, 2) > 0 || i_inputHandler->yvalue(0, 2) < 0)
        {
            m_velocity.setY(1 * i_inputHandler->yvalue(0, 2));
        }
    }
    if(i_inputHandler->getButtonState(0,3)){
        m_velocity.setX(1);
    }
}

// ENEMY
Enemy::Enemy(const LoaderParams *pParmas) : SDLGameObject(pParmas)
{
}
void Enemy::draw()
{
    SDLGameObject::draw();
}
void Enemy::update()
{
    m_position.setX(m_position.getX() + 1);
    m_position.setY(m_position.getY() + 1);
}
void Enemy::clean()
{
}