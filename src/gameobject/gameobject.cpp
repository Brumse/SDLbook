#include "gameobject.h"
#include <iostream>
void GameObject::draw()
{
    std::cout << "draw game object" << std::endl;
}
void GameObject::update()
{
    std::cout << "update game object" << std::endl;
}
void GameObject::clean()
{
    std::cout << "clean game objects" << std::endl;
}

void Player::draw()
{
    GameObject::draw();
    std::cout << "draw player" << std::endl;
}
void Player::update()
{
    std::cout << "update player";
    m_x = 10;
    m_y = 20;
}
void Player::clean()
{
    GameObject::clean();
    std::cout << "clean player";
}
