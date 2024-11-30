#include <SDL.h>
#include <iostream>

SDL_Window *g_pWindow = nullptr;
SDL_Renderer *g_pRenderer = nullptr;

int main(int argc, char *argv[])
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		const size_t sz = 4096;
		char err[sz];
		SDL_GetErrorMsg(err, sz);
		std::cout << "Could not init SDL: " << err << std::endl;
		return 1;
	}

	g_pWindow = SDL_CreateWindow("Chapter 1 Setting up SDL",
								 SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
								 640, 480, SDL_WINDOW_SHOWN);

	if (g_pWindow == nullptr)
	{
		std::cout << "Could not create window" << std::endl;
		return 1;
	}

	g_pRenderer = SDL_CreateRenderer(g_pWindow, -1, 0);

	SDL_SetRenderDrawColor(g_pRenderer, 0, 0, 0, 255);
	SDL_RenderClear(g_pRenderer);
	SDL_RenderPresent(g_pRenderer);
	SDL_Delay(5000);

	SDL_Quit();

	return 0;
}
