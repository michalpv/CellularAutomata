#include <SDL.h>
#include <stdio.h>

#include "defs.h"
#include "gfx.h"

int initSDL(SDL_Window** window, SDL_Renderer** renderer) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "SDL failed to initialize; %s\n", SDL_GetError());
        return 1; // Return 1 on failure
    }

    *window = SDL_CreateWindow(
        "Conway's Game of Life",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WIDTH,
        HEIGHT,
        0
    );
    if (*window == NULL) {
        fprintf(stderr, "SDL failed to create window; %s\n", SDL_GetError());
        return 1;
    }

    *renderer = SDL_CreateRenderer(
        *window,
        -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );
    if (*renderer == NULL) {
        fprintf(stderr, "SDL failed to create renderer; %s\n", SDL_GetError());
        return 1;
    }

    return 0;
}

void render(int* cells, SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 0xEA, 0xF0, 0xCE, 255);
    SDL_RenderClear(renderer);

    SDL_Rect liveCell = {0, 0, CELLW, CELLH};
    SDL_SetRenderDrawColor(renderer, 0x3F, 0x33, 0x4D, 255);
    for (int y = 0; y < HEIGHT/CELLH; y++) {
        for (int x = 0; x < WIDTH/CELLW; x++) {
            if (cells[y*WIDTH/CELLW + x] == 1) {
                liveCell.x = x*CELLW;
                liveCell.y = y*CELLH;
                SDL_RenderFillRect(renderer, &liveCell);
            }
        }
    }

    SDL_RenderPresent(renderer);
}