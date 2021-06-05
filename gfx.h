#ifndef GFX
#define GFX
#include <SDL.h>

int initSDL(SDL_Window** window, SDL_Renderer** renderer);
void render(int* cells, SDL_Renderer* renderer);

#endif