#pragma once

#include <vector>

#include "SDL.h"
#include <SDL_image.h>
#include "TextureManager.h"
#include "gameobject.h"

class Game
{
public:
    Game() {}
    ~Game() {}

    bool init(const char *title, int xpos, int ypos, int width,
              int height, bool fullscreen);
    void render();
    void update();
    void handleEvents();
    void clean();
    bool running() { return m_bRunning; }

private:
    SDL_Window *m_pWindow;
    SDL_Renderer *m_pRenderer;
    int m_currentFrame;
    bool m_bRunning;
    GameObject* m_go;
    GameObject* m_player;

    std::vector<GameObject*> m_gameObjects;
};

