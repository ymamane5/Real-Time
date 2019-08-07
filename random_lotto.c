#include<stdio.h>
#include<stdlib.h>
#include<math.h>

void print_board(int board[][]);

#define ROWS 5
#define COLUMNS 10

int main()
{
int board[10][5] = {0};

print_board(board);

}

void print_board(int board[][])
{
	int i, j;

	for(i = 0; i < ROWS; i++) 
	{
		for(j = 0; j < COLUMNS; j++)
		{
			printf("%d ",board[j][i]);
		}
	printf("\n");
	}
}


