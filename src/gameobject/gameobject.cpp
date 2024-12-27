#include "gameobject.h"
#include <iostream>
#include "TextureManager.h"
#include "game.h"

// SDL GAME OBJECT
SDLGameObject::SDLGameObject(const LoaderParams *pParams) : GameObject(pParams)
{
    m_x = pParams->getX();
    m_y = pParams->getY();
    m_width = pParams->getWidth();
    m_height = pParams->getHeight();
    m_textureID = pParams->getTextureID();

    m_currentRow = 1;
    m_currenctFrame = 1;
}
void SDLGameObject::draw()
{
    TextureManager::Instance()->drawFrame(m_textureID, m_x, m_y, m_width, m_height, m_currentRow, m_currenctFrame, Game::instance()->getRenderer());
}

void SDLGameObject::update()
{
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
    m_x -= 1;
    m_currenctFrame = int(((SDL_GetTicks() / 100) % 6));
}
void Player::clean()
{
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
    m_x += 1;
    m_currenctFrame = int(((SDL_GetTicks() / 100) % 6));
}
void Enemy::clean()
{
}