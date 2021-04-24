#include <SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include "SDL.h"
#include "logic.h"

// Game of Life functions
//void updateCells(char a[][GRID_WIDTH]); // takes cells array as input
//int countLivingNeighbours(char a[][GRID_WIDTH], int x, int y);
int ** init();
void output(char a[][GRID_WIDTH]);
int **map;
int getrow();
int getcol();


int main(int argc, char *argv[]){
    // Initialise SDL
    SDL_Init(SDL_INIT_VIDEO);
	char choose;
	//INITIALIZE
	printf("Please choose the mode:\n");
	printf("1.read from the last file\n");
	printf("2.start a new world\n");
	printf("Enter your choose:");
	scanf("%c", &choose);
    SDL_Window *window;
    SDL_Renderer *renderer;
    int row=50;
    int col=50;
    char  cells[row][col];
	switch(choose)
	{
		case '1':
			{
				row=getrow();
				col=getcol();
				FILE * fp;
				fp = fopen("final.txt", "r");
				printf("%d, %d\n", row, col);
				GRID_HEIGHT = row;
				GRID_WIDTH = col;
				//char cell[row][col];
				//cells = cell;
				cells[row][col];
				SCREEN_HEIGHT = GRID_HEIGHT * CELL_SIZE;
				SCREEN_WIDTH = GRID_WIDTH * CELL_SIZE;
				window = createWindow("Game of Life");
				renderer = createRenderer(window);
				if(NULL != fp)
				{
					for(int i=0 ; i < row ; i++)
					{
						for(int j = 0 ; j < col ; j++)
						{
							fscanf(fp, "%c", &cells[i][j]);
							printf("%c", cells[i][j]);		
						}
						fscanf(fp, "\n");
						printf("\n"); 
					}
				}
				break;
			}
			 
		case '2':
			{
				//				printf("Please enter the width: ");
//				scanf("%d", &col);
//				printf("Please enter the height: ");
//				scanf("%d", &row);
//				printf("%d, %d\n", row, col);
				GRID_HEIGHT = col;
				GRID_WIDTH = row;
//				cells[GRID_WIDTH][GRID_HEIGHT];
				SCREEN_HEIGHT = GRID_HEIGHT * CELL_SIZE;
				SCREEN_WIDTH = GRID_WIDTH * CELL_SIZE;
				window = createWindow("Game of Life");
				renderer = createRenderer(window);
				//getchar();
			    //char cells[GRID_HEIGHT][GRID_WIDTH];
			    
			    for(int i = 0; i < GRID_HEIGHT; i++)
				{
			        for(int j = 0; j < GRID_WIDTH; j++)
					{
			            cells[i][j] = DEAD;
			            //printf("%c", cells[cy][cx]);
			        }
			        //printf("\n");
			    }
				break;
			}	
	}

    // Setup event handling + mouse co-ordinate handling
    SDL_Event event;
    int mouseX, mouseY;
    bool mouse_left_down = false;
    bool mouse_right_down = false;	
	
	int quit = 1;
	//char ch;
	while(1)
	{
        while(SDL_PollEvent(&event) != 0)
		{
            switch(event.type)
			{
                case SDL_QUIT: // Check if user has quit
                	//SDL_Log("Event type is %d", event.type);
                    return 1;

                // Check if user is HOLDING left or right mouse button
                case SDL_MOUSEBUTTONDOWN: 
				case SDL_MOUSEBUTTONUP:
					//SDL_Log("Event type is %d", event.type);
                    switch(event.button.button)
					{
                        case SDL_BUTTON_LEFT: 
							mouse_left_down = !mouse_left_down;
							break;
                        case SDL_BUTTON_RIGHT: 
							mouse_right_down = !mouse_right_down; 
							break;
                    }
					
                // If user presses space, simulate a single change
                
				case SDL_KEYDOWN:
                    if(event.key.keysym.sym == SDLK_SPACE){
						updateCells(cells);
                		output(cells);
					} 
                    
                		

            }
        }
	//updateCells(cells);
	
		// Get user mouse button input - left click gives life to cell at current co-ords, right click kills
        SDL_GetMouseState(&mouseX, &mouseY);
        //printf("mouseX:%d, mouseY:%d\n", mouseX, mouseY);
        if(mouse_left_down == true)
        {
        	cells[mouseY / CELL_SIZE][mouseX / CELL_SIZE] = ALIVE;
            //printf("cell[%d, %d] = %c\n",mouseX / CELL_SIZE,mouseY / CELL_SIZE, cells[mouseY / CELL_SIZE][mouseX / CELL_SIZE]);
		}
            
        else if(mouse_right_down == true)
            cells[mouseY / CELL_SIZE][mouseX / CELL_SIZE] = DEAD;
        // Set screen colour to white
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

        // Render white to screen (clear screen)
        SDL_RenderClear(renderer);

        // Draw the grid and living cells
        drawGrid(renderer);
        drawCells(renderer, cells);

        // Update screen
        SDL_RenderPresent(renderer);
        
        SDL_Delay(40);
    }

    // Exit SDL and SDL_image
    SDL_Quit();
    return 0;
}

void output(char a[][GRID_WIDTH])
{
	FILE * filename;
	filename = fopen("final.txt", "w+");
	int count = 0;
	int row, col;
	for(row = 0 ; row < GRID_HEIGHT; row++)
	{
		for(col = 0 ; col < GRID_WIDTH ; col++)
		{
			fprintf(filename, "%c", a[row][col]);
		}
		fprintf(filename, "\n");
	}
	fclose(filename);	
} 

int getrow()
{
	FILE * file;
	file = fopen("init.txt", "r");
	int rownum=1;
	char ch;
	while((ch=fgetc(file))!= EOF) 
	{
		if(ch == '\n')
		{
			rownum++;
			//colnum=0;
		}
	}
	fclose(file);
	return rownum;
}

int getcol()
{
	FILE * file;
	file = fopen("init.txt", "r");
	int rownum=1;
	int colnum=0;
	char ch;
	while((ch=fgetc(file))!= EOF) 
	{
		if(ch == '\n')
		{
			rownum++;
			colnum=0;
		}
		else
		{
			colnum++;
		}
	}
	printf("colnum:%d\n", colnum); 
	fclose(file);
	return colnum;
}
