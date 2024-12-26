#include "gameobject.h"
#include <iostream>
#include "TextureManager.h"

// GAME OBJECT
void GameObject::load(int x, int y, int width, int height, std::string textureID)
{
    m_x = x;
    m_y = y;
    m_width = width;
    m_height = height;
    m_textureID = textureID;

    m_currentRow = 1;
    m_currentFrame = 1;
}

void GameObject::draw(SDL_Renderer *pRenderer)
{
    TextureManager::Instance()->drawFrame(m_textureID, m_x, m_y, m_width, m_height, m_currentRow, m_currentFrame, pRenderer);
}
void GameObject::update()
{
    m_x += 1;
}
void GameObject::clean()
{
    std::cout << "clean game objects" << std::endl;
}

// PLAYER
void Player::load(int x, int y, int width, int height, std::string textureID)
{
    GameObject::load(x, y, width, height, textureID);
}
void Player::draw(SDL_Renderer *pRenderer)
{
    GameObject::draw(pRenderer);
}
void Player::update()
{
    m_x -= 1;
}
void Player::clean()
{
    GameObject::clean();
    std::cout << "clean player";
}
