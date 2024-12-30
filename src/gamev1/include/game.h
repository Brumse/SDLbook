#pragma once

#include <vector>
#include "SDL.h"
#include <SDL_image.h>
#include "TextureManager.h"
#include "gameobject.h"




class Game
{
public:

    bool init(const char *title, int xpos, int ypos, int width,
              int height, bool fullscreen);
    void render();
    void update();
    void handleEvents();
    void clean();
    bool running() { return m_bRunning; }
    SDL_Renderer* getRenderer()const {return m_pRenderer;}

    static Game* instance();
private:
    Game(){}
    static Game* s_pInstance;

    SDL_Window *m_pWindow;
    SDL_Renderer *m_pRenderer;
    int m_currentFrame;
    bool m_bRunning;
    GameObject* m_go;
    GameObject* m_player;
    GameObject* m_enemy;

    std::vector<GameObject*> m_gameObjects;
};

