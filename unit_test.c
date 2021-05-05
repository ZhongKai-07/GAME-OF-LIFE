#include "unity.h"
#include "SDL.h"
#include "unity.h"

int GRID_HEIGHT = 5;
int GRID_WIDTH = 5;
void test_getcol(){
	int col = getcol();
	
	TEST_ASSERT_EQUAL_INT(30, col);
}

void test_getrow(){
	int row = getrow();
	
	TEST_ASSERT_EQUAL_INT(30, row);
}

void test_createWindow(){
	SDL_Window * w = createWindow("game");
	
	//TEST_ASSERT_NULL_MESSAGE(w,"xxx");
	TEST_ASSERT_NOT_NULL_MESSAGE(w, "---");
}

void test_createRenderer(){
	SDL_Window * w = createWindow("game");
	SDL_Renderer * r = createRenderer(w);
	
	//TEST_ASSERT_NULL_MESSAGE(w,"xxx");
	TEST_ASSERT_NOT_NULL_MESSAGE(r, "create the renderer");
	//TEST_ASSERT_NULL_MESSAGE(r, "cannot create the valid renderer");
}

void test_countLivingNeighbours(){
	char c[][5] = {
						{'1', '0', '1', '1', '0'},
						{'1', '0', '1', '1', '0'},
						{'0', '0', '0', '1', '0'},
						{'1', '0', '1', '1', '0'},
						{'1', '0', '1', '1', '0'}
					};
	int num1, num2;
//	int GRID_HEIGHT = 5;
//	int GRID_WIDTH = 5;
	num1 = countLivingNeighbours(c, 1, 3);
	num2 = countLivingNeighbours(c, 0, 0);
	TEST_ASSERT_EQUAL_INT(4, num1);
	TEST_ASSERT_EQUAL_INT(1, num2);
}

void test_updateCells(){
//	int GRID_HEIGHT = 5;
//	int GRID_WIDTH = 5;
	char c[][5] = {
						{'1', '0', '1', '1', '0'},
						{'1', '0', '1', '1', '0'},
						{'0', '0', '0', '1', '0'},
						{'1', '0', '1', '1', '0'},
						{'1', '0', '1', '1', '0'}
					};
	updateCells(c);
	char state = c[2][1];
	TEST_ASSERT('0' == state);
	
} 

void test_array(){
	int a[3] = {0, 0, 0};
	int b[3] = {0, 0, 0};
	TEST_ASSERT_EQUAL_INT_ARRAY(a, b, 3);
} 

void setUp(){

}
void tearDown(){

}

int main(int argc, char * argv[]) {
  UNITY_BEGIN();
  RUN_TEST(test_getrow);
  RUN_TEST(test_getcol);
  RUN_TEST(test_createWindow);
  RUN_TEST(test_createRenderer);
  RUN_TEST(test_countLivingNeighbours);
  RUN_TEST(test_updateCells);
  RUN_TEST(test_array); 

  return UNITY_END();
}
