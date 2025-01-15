#pragma once

#include <vector>
#include "SDL.h"
#include <SDL_image.h>
#include "TextureManager.h"
#include "gameobject.h"
#include "gamestatemachine.h"

enum game_state
{
    MENU = 0,
    PLAY = 1,
    GAMEOVER = 2
};

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
    SDL_Renderer *getRenderer() const { return m_pRenderer; }

    static Game *instance();
    

private:
    Game() {}
    static Game *s_pInstance;

    SDL_Window *m_pWindow;
    SDL_Renderer *m_pRenderer;
    int m_currentFrame;
    bool m_bRunning;
    GameObject *m_go;
    GameObject *m_player;
    GameObject *m_enemy;
    

    GameStateMachine* m_pGameStateMachine;
    std::vector<GameObject *> m_gameObjects;
};
