#pragma once
#include "SDL.h"
#include <string>
#include "vector2D.h"

class LoaderParams;

class GameObject
{
public:
    virtual void draw() = 0;
    virtual void update() = 0;
    virtual void clean() = 0;

protected:
    GameObject(const LoaderParams *pParams) {}
    virtual ~GameObject() {}
};

class SDLGameObject : public GameObject
{
public:
    SDLGameObject(const LoaderParams *pParams);

    virtual void draw();
    virtual void update();
    virtual void clean();

protected:
    Vector2D m_postition;
    Vector2D m_velocity;
    Vector2D m_acceleration;
    
    int m_width;
    int m_height;
    int m_currentRow;
    int m_currentFrame;
    std::string m_textureID;
};

class Player : public SDLGameObject
{
public:
    Player(const LoaderParams *pParams);

    virtual void draw();
    virtual void update();
    virtual void clean();
};

class Enemy : public SDLGameObject
{
public:
    Enemy(const LoaderParams *pParams);

    virtual void draw();
    virtual void update();
    virtual void clean();

};
class LoaderParams
{
public:
    LoaderParams(int x, int y, int width, int height, std::string textureID) 
        : m_position(x, y), m_width(width), m_height(height), m_textureID(textureID)
    {
    }

    int getX() const { return m_position.getX(); }
    int getY() const { return m_position.getY(); }
    int getWidth() const { return m_width; }
    int getHeight() const { return m_height; }
    std::string getTextureID() const { return m_textureID; }

private:
    Vector2D m_position;

    int m_width;
    int m_height;
    std::string m_textureID;
};