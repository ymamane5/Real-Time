#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void print_board(char board[][]);
void update_board(char board[][], int arr[]);

#define ROWS 5
#define COLUMNS 10
#define SIZE 6

int main()
{
	char board[ROWS][COLUMNS];
	int random_numbers[SIZE], temp_rand;

	/* initialize board */
	for(i = 0; i < ROWS; i++) 
		for(j = 0; j < COLUMNS; j++)
			board[i][j] = '-';

	srand(time(0));

	while(i < SIZE)
	{
		temp_rand = rand() % 50;
		/*
		check if exist
			/*continue;
		else
			random_numbers[i++] = temp_rand;
		*/
	}
	update_board(board);
	print_board(board);

}

void update_board(char board[][], int arr[])
{
	int row, col;
	
	for(i = 0; i < SIZE; i++)
	{
		row = arr[i] <= 10 ? arr[i] : arr[i] / 10;
		col = arr[i] <= 10 ? : arr[i] % 10;
		board[row][col] = '+';
	}
}

void print_board(char board[][COLUMNS])
{
	int i, j;
	
	printf("  ");
	for(i = 1; i <= COLUMNS; i++) 
		printf("%d ",i);
	
	printf("\n");

	for(i = 0; i < ROWS; i++) 
	{
		printf("%d ", i);
			for(j = 0; j < COLUMNS; j++)
			{
				printf("%c ",board[i][j]);
			}
		printf("\n");
	}
}
