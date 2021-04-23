#include <SDL.h>
#include <stdio.h>
#include <stdbool.h>

#define CELL_SIZE 10
#define ALIVE '1'
#define DEAD '0'
//#define GRID_WIDTH 50
//#define GRID_HEIGHT 50
//#define SCREEN_WIDTH (GRID_WIDTH * CELL_SIZE)
//#define SCREEN_HEIGHT (GRID_HEIGHT * CELL_SIZE)
int GRID_WIDTH;
int GRID_HEIGHT;
int SCREEN_WIDTH;
int SCREEN_HEIGHT;
//typedef enum {DEAD, ALIVE} State;
//typedef struct{
//    int x;
//    int y;
//    State state;
//} Cell;


// SDL related functions
SDL_Window *createWindow(char *title);
SDL_Renderer *createRenderer(SDL_Window *window);
void drawGrid(SDL_Renderer *r);
void drawCells(SDL_Renderer *r, char a[][GRID_WIDTH]);

// Game of Life functions
void updateCells(char a[][GRID_WIDTH]); // takes cells array as input
int countLivingNeighbours(char a[][GRID_WIDTH], int x, int y);
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
	
//	int row, col;
//	row=getrow();
//	col=getcol();
//	FILE * fp;
//	
//	
//	
//	//int GRID_WIDTH, GRID_HEIGHT;
//	fp = fopen("init.txt", "r");
//	fscanf(fp, "%dX%d", &row, &col);
//	printf("%d, %d\n", row, col);
//	GRID_HEIGHT = row;
//	GRID_WIDTH = col;
//	SCREEN_HEIGHT = GRID_HEIGHT * CELL_SIZE;
//	SCREEN_WIDTH = GRID_HEIGHT * CELL_SIZE;
	//printf("%d, %d", SCREEN_HEIGHT,SCREEN_WIDTH );
//	char cells[row][col];	
	// Create window and renderer
//    SDL_Window *window = createWindow("Game of Life");
//    SDL_Renderer *renderer = createRenderer(window);
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

//	printf("%d\n", cells[0]);
//	printf("%d\n", cells[0]);
//	printf("%d\n", cells[0]);
//	printf("%d\n", cells[0]);
//    // Create window and renderer
//    SDL_Window *window = createWindow("Game of Life");
//    SDL_Renderer *renderer = createRenderer(window);

    // Setup event handling + mouse co-ordinate handling
    SDL_Event event;
    int mouseX, mouseY;
    bool mouse_left_down = false;
    bool mouse_right_down = false;	
	
	//int ** cells = init();
    // Set all cells to initial state of dead
//    int cells[GRID_HEIGHT][GRID_WIDTH];
//    int cx, cy;
//    for(cy = 0; cy < GRID_HEIGHT; cy++){
//        for(cx = 0; cx < GRID_WIDTH; cx++){
//            cells[cy][cx] = DEAD;
//        }
//    }
//	int a;
//	srand((unsigned)time(NULL));
//	int r,c;
//	for(r=0; r < GRID_HEIGHT ; r++)
//	{
//		//cells[r] = (int *)malloc(GRID  *sizeof(int));
//		for(c=0 ; c < GRID_WIDTH ; c++)
//		{
//			int a = rand()%2;
//			cells[r][c] = a;
//		}
//	}
	int quit = 1;
	char ch;
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
    // Draw living cells
//    int cx, cy;
//    for(cx = 0; cy < GRID_WIDTH; cx++){
//        for(cy = 0; cy < GRID_HEIGHT; cy++){
//        	printf("%c\n", a[cx][cy]);
//            if(a[cx][cy] == '1'){
//                // Set cell x/y pos
//                cellRect.x = (cx) * CELL_SIZE;
//                cellRect.y = (cy) * CELL_SIZE;
//
//                SDL_SetRenderDrawColor(r, 200, 0, 0, 1);
//                SDL_RenderFillRect(r, &cellRect);
//            }
//        }
//    }
//	printf("%c\n", a[0][1]);
//	printf("%c\n", a[0][2]);
//	printf("%c\n", a[0][3]);
//	printf("%c\n", a[0][4]);
//	printf("%c\n", a[0][5]);
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
