#ifndef logic_GUARD_H
#define logic_GUARD_H

#include <stdio.h>
#include <stdbool.h>
#include "SDL.h"
void updateCells(char a[][GRID_WIDTH]); // takes cells array as input


int countLivingNeighbours(char a[][GRID_WIDTH], int x, int y);

int getrow();
int getcol();

int output(char a[][GRID_WIDTH]);

#endif
