#include <stdio.h>
#include <SDL.h>
#define CELL_SIZE 10
#define ALIVE '1'
#define DEAD '0'
int GRID_WIDTH;
int GRID_HEIGHT;
int SCREEN_WIDTH;
int SCREEN_HEIGHT;
SDL_Window *createWindow(char *title);
SDL_Renderer *createRenderer(SDL_Window *window);
void drawGrid(SDL_Renderer *r);
void drawCells(SDL_Renderer *r, char a[][GRID_WIDTH]);

