#include "SDL.h"

SDL_Window *createWindow(char *title){
    SDL_Window *window = SDL_CreateWindow(
        title,                  // Title
        SDL_WINDOWPOS_CENTERED, // Initial window x position
        SDL_WINDOWPOS_CENTERED, // Initial window y position
        SCREEN_WIDTH,           // Window Width
        SCREEN_HEIGHT,          // Window Height
        0                       // Flags
    );

    if(window == NULL){
        printf("Failed to create window. %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    return window;
}

SDL_Renderer *createRenderer(SDL_Window *window){
    SDL_Renderer *renderer = SDL_CreateRenderer(
        window,                     // Window
        -1,                         // Monitor index (-1 for first available)
        SDL_RENDERER_ACCELERATED    // Flags
    );

    if(renderer == NULL){
        printf("Failed to create renderer. %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    return renderer;
}

void drawGrid(SDL_Renderer *r){
    // Draw vertical grid lines
    for(int v = CELL_SIZE; v < SCREEN_WIDTH; v += CELL_SIZE){
        // Set draw colour to grey
        SDL_SetRenderDrawColor(r, 110, 110, 110, 110);

        // Draw vertical line
        SDL_RenderDrawLine(r, v, 0, v, SCREEN_HEIGHT);
    }

    // Draw horizontal grid lines
    for(int h = CELL_SIZE; h < SCREEN_HEIGHT; h += CELL_SIZE){
        // Set draw colour to grey
        SDL_SetRenderDrawColor(r, 110, 110, 110, 110);

        // Draw horizontal line
        SDL_RenderDrawLine(r, 0, h, SCREEN_WIDTH, h);
    }
}

void drawCells(SDL_Renderer *r, char a[][GRID_WIDTH]){
    // Define cell width/height
    SDL_Rect cellRect;
    cellRect.w = CELL_SIZE; // Same size as one cell +1 so it covers the grid line fully
    cellRect.h = CELL_SIZE; // Same size as one cell +1 so it covers the grid line fully
    int x, y;
    for(y = 0; y < GRID_HEIGHT; y++){
        for(x = 0; x < GRID_WIDTH; x++){
            if(a[y][x] == ALIVE){
                // Set cell x/y pos
                cellRect.x = (x) * CELL_SIZE;
                cellRect.y = (y) * CELL_SIZE;

                SDL_SetRenderDrawColor(r, 200, 0, 0, 1);
                SDL_RenderFillRect(r, &cellRect);
            }
        }
    }
}
