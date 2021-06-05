#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "defs.h"
#include "gfx.h"
#include "life.h"

int main(int argc, char* argv[]) {
    SDL_Window* win = NULL;
    SDL_Renderer* rndr = NULL;

    if (initSDL(&win, &rndr)) {
        return 1;
    }

    // Setup grid
    // TODO: integers are not necessary, even 1 bit will suffice (though int is best if memory is not an issue)
    int* cells = (int*) malloc(sizeof(int)*HEIGHT/CELLH*WIDTH/CELLW);
    srand(time(NULL)); // Seed RNG before using it in setupCells
    setupCells(cells);

    int state = 1;
    // Simulation loop
    while (state == 1) {
        // For some reason, calling SDL_GetTicks() causes a consistent pattern of live cells to appear at the bottom of the window
        //int start_time = SDL_GetTicks();
        render(cells, rndr);
        update(cells);
        do {
            // TODO: Replace with calculated delay based on delta time and FPS target
            SDL_Delay(50);
            SDL_Event e;
            SDL_PollEvent(&e);
            switch (e.type) {
                case SDL_QUIT:
                    state = 0;
                    break;
                case SDL_KEYDOWN:
                    if (e.key.keysym.sym == SDLK_q) {
                        state = 0; // Exit state
                    }
                    if (e.key.keysym.sym == SDLK_SPACE) {
                        state = (state == 1) ? 2 : 1; // Toggle paused and running state
                    }
                    if (e.key.keysym.sym == SDLK_s && state == 2) { // "Step" (render and update once)
                        render(cells, rndr);
                        update(cells);
                    }
                    if (e.key.keysym.sym == SDLK_r) {
                        setupCells(cells); // Reset cells (call setupCells() again and reinit cells array)
                        // If called multiple times within 1 second, it will likely be the same setup
                    }

                    break;
            }
        } while (state == 2);
        // Print FPS count to console:
        // For some reason, calling SDL_GetTicks() causes a consistent pattern of live cells to appear at the bottom of the window
        //printf("FPS: %f\n", 1.0/((SDL_GetTicks() - start_time)/1000.0));
    }
    free(cells);
    
    // Destroy SDL stuff and quit
    SDL_DestroyRenderer(rndr);
    SDL_DestroyWindow(win);
    SDL_Quit();

    return 0;
}