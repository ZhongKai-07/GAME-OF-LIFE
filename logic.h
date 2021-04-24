#include <stdio.h>
#include <stdbool.h>
#include "SDL.h"
void updateCells(char a[][GRID_WIDTH]); // takes cells array as input


int countLivingNeighbours(char a[][GRID_WIDTH], int x, int y);
