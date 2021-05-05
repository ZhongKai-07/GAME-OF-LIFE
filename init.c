// c 语言以字符形式读取文件(ANSI编码)
#include <stdio.h>
#define ALVE '1'
#define DEAD '0'
int main()
{
    FILE* fp;
    //char ch;
    char map[5][5];
    int newmap[10][10];
    int colnum = 0;
    int rownum = 1;
    //int row, col;
    fp = fopen("init.txt", "r");
    int row = 5;
    int col = 5;

	int num=1;
	char ch;
	while((ch=fgetc(fp))!= EOF) 
	{
		if(ch == '\n')
		{
			rownum++;
			colnum=0;
		}
		else
		{
			colnum++;
			num++;
		}
	}
	num--;
    printf("\nnum:%d\n", num);
    printf("row:%d\n", rownum);
    printf("col:%d\n", colnum);
	printf("\n");
 	
    return 0;
}
