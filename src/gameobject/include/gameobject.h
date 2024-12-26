#pragma once

class GameObject
{
public:
    virtual void draw();
    virtual void update();
    virtual void clean();
    
protected:
    int m_x;
    int m_y;
};

class Player:public GameObject{
public:
    void draw() override;
    void update() override;
    void clean() override;


};