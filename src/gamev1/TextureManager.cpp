#include "TextureManager.h"


TextureManager* TextureManager::s_pInstance = nullptr;

bool TextureManager::load(std::string fileName, std::string id, SDL_Renderer *pRenderer)
{
    SDL_Surface *pTempSurface = IMG_Load(fileName.c_str());

    if (pTempSurface == 0)
    {
        return false;
    }
    SDL_Texture *pTexture = SDL_CreateTextureFromSurface(pRenderer, pTempSurface);
    SDL_FreeSurface(pTempSurface);

    if (pTexture != 0)
    {
        m_textureMap[id] = pTexture;
        return true;
    }

    return false;
}

void TextureManager::draw(std::string id, int x, int y, int width, int height, SDL_Renderer *pRenderer, SDL_RendererFlip flip)
{
    SDL_Rect srcRect;
    srcRect.x = 0;
    srcRect.y = 0;
    srcRect.w = width;
    srcRect.h = height;

    SDL_Rect destRect;
    destRect.w = width;
    destRect.h = height;
    destRect.x = x;
    destRect.y = y;

    SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect, &destRect, 0, 0, flip);
}

void TextureManager::drawFrame(std::string id, int x, int y, int width, int height, int currentRow, int currentFrame, SDL_Renderer *pRenderer, SDL_RendererFlip flip)
{

    SDL_Rect srcRect;
    srcRect.x = width * currentFrame;
    srcRect.y = height * (currentRow - 1);
    srcRect.w = width;
    srcRect.h = height;
    
    SDL_Rect destRect;
    destRect.w = width;
    destRect.h = height;
    destRect.x = x;
    destRect.y = y;

    SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect, &destRect, 0, 0, flip);
}