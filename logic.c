#include "logic.h"

/*
1. Any live cell with fewer than two live neighbours dies, as if caused by underpopulation.
2. Any live cell with two or three live neighbours lives on to the next generation.
3. Any live cell with more than three live neighbours dies, as if by overpopulation.
4. Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.
*/
void updateCells(char a[][GRID_WIDTH]){
    int new[GRID_HEIGHT][GRID_WIDTH];
    int cy, cx; // vertical count, horizontal count

    for(cy = 0; cy < GRID_HEIGHT; cy++){
        for(cx = 0; cx < GRID_WIDTH; cx++){
            // Any live cell with fewer than two live neighbours dies, as if caused by underpopulation.
            if(a[cy][cx] == ALIVE && countLivingNeighbours(a, cx, cy) < 2)
                new[cy][cx] = DEAD;

            // Any live cell with two or three live neighbours lives on to the next generation.
            else if(a[cy][cx] == ALIVE && (countLivingNeighbours(a, cx, cy) == 2 || countLivingNeighbours(a, cx, cy) == 3))
                new[cy][cx] = ALIVE;

            // Any live cell with more than three live neighbours dies, as if by overpopulation.
            else if(a[cy][cx] == ALIVE && countLivingNeighbours(a, cx, cy) > 3)
                new[cy][cx] = DEAD;

            // Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.
            else if(a[cy][cx] == DEAD && countLivingNeighbours(a, cx, cy) == 3)
                new[cy][cx] = ALIVE;

            else
                new[cy][cx] = DEAD;
        }
    }

    // Update all cells into new states
    for(cy = 0; cy < GRID_HEIGHT; cy++){
        for(cx = 0; cx < GRID_WIDTH; cx++){
            a[cy][cx] = new[cy][cx];
        }
    }
}

// THERE'S NO ERROR CHECKING HERE WHICH IS BAD
// Should ideally check if a cell even exists before checking its state
int countLivingNeighbours(char a[][GRID_WIDTH], int x, int y){
    int count = 0, cx, cy;

    for(cy = y - 1; cy <= y + 1; cy++){
        for(cx = x - 1; cx <= x + 1; cx++){

            // Ensure neighbouring cell is not out of bounds
            if(!(cy < 0 || cx < 0 || cy >= GRID_HEIGHT || cx >= GRID_WIDTH)){
                // If there is a living neighbouring cell, add to count
                if(a[cy][cx] == ALIVE)
                    count++;

                // disregard current cell as it is not a neighbour
                if(a[cy][cx] == ALIVE && cx == x && cy == y)
                    count--;
            }


        }
    }

    return count;
}
