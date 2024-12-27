#include "gameobject.h"
#include <iostream>
#include "TextureManager.h"
#include "game.h"

// SDL GAME OBJECT
SDLGameObject::SDLGameObject(const LoaderParams *pParams) : GameObject(pParams), m_postition(pParams->getX(), pParams->getY())
{
    m_width = pParams->getWidth();
    m_height = pParams->getHeight();
    m_textureID = pParams->getTextureID();

    m_currentRow = 1;    // ett eller l?
    m_currentFrame = 1; // ett eller l?
}
void SDLGameObject::draw()
{
    TextureManager::Instance()->drawFrame(m_textureID, (int)m_postition.getX(), (int)m_postition.getY(), m_width, m_height, m_currentRow, m_currentFrame, Game::instance()->getRenderer());
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
    m_postition.setX(m_postition.getX() - 1);
    m_postition.setY(m_postition.getY() - 1);
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
    m_postition.setX(m_postition.getX() + 1);
    m_postition.setY(m_postition.getY() + 1);
}
void Enemy::clean()
{
}