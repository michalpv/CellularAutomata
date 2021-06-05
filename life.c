#include <time.h>
#include <string.h> // for memcpy()
#include <stdlib.h>

#include "defs.h"
#include "life.h"

void update(int* cells1) {
    // cells2 represents new state of the grid
    int* cells2 = (int*) calloc(HEIGHT/CELLH*WIDTH/CELLW, sizeof(int));
    for (int y = 0; y < HEIGHT/CELLH; y++) {
        for (int x = 0; x < WIDTH/CELLW; x++) {
            // Check if cell is alive or dead, then change state depending on neighbours
            // If dead:
            int neighbours = getNeighbours(x, y, cells1);
            if (cells1[y*WIDTH/CELLW + x] == 0) {
                if (neighbours == 3) {
                    cells2[y*WIDTH/CELLW + x] = 1;
                }
            }
            // If alive:
            else {
                // Stay alive only if 
                if (!(neighbours < 2 || neighbours > 3)) {
                    cells2[y*WIDTH/CELLW + x] = 1;
                }
                // ... Otherwise die (cells2 is already initialized to 0)
            }
        }
    }
    // Copy data from cells2 into cells1, effectively updating the grid
    // TODO: (try returning cells2 and freeing cells1, get rid of memcpy call)
    memcpy(cells1, cells2, sizeof(int)*HEIGHT/CELLH*WIDTH/CELLW);
    free(cells2);
}

int getNeighbours(int x, int y, int* cells) { // X and Y correlate to x, y coords of cell on grid
    int count = 0;
    for (int xx = -1; xx <= 1; xx++) {
        for (int yy = -1; yy <= 1; yy++) {
            int offx = x+xx;
            int offy = y+yy;
            // Wrap around edges on left & right:
            if (offx == -1) {
                offx = WIDTH/CELLW - 1;
            }
            else if (offx == WIDTH/CELLW) {
                offx = 0;
            }
            // Wrap around edges on top & bottom:
            if (offy == -1) {
                offy = HEIGHT/CELLH - 1;
            }
            else if (offy == HEIGHT/CELLH) {
                offy = 0;
            }
            
            // Check that neighbouring cells are alive, excluding the given cell itself
            if (cells[(offy)*WIDTH/CELLW + (offx)] && !(yy == 0 && xx == 0)) {
                count++;
            }
        }
    }

    return count;
}

void setupCells(int* cells) {
    // Instead, make window width/height a product of cell pixel size and count
    for (int i = 0; i < HEIGHT/CELLH*WIDTH/CELLW; i++) {
        // 1/CHANCE chance to spawn living cell on setup
        // TODO: use calloc when creating cells array to avoid writing 0 here (not much of an improvement)
        cells[i] = ((rand() % CHANCE) == 0) ? 1 : 0;
    }
}