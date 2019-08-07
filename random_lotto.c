#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define ROWS 5
#define COLUMNS 10
#define SIZE 6

void print_board(char board[ROWS][COLUMNS]);
void update_board(char board[ROWS][COLUMNS], int arr[]);
int check_dup(int* arr, int num);

int main()
{
	char board[ROWS][COLUMNS];
	int temp_rand, i, j, random_numbers[SIZE] = {0,0,0,0,0,0};

	/* initialize board */
	for(i = 0; i < ROWS; i++) 
		for(j = 0; j < COLUMNS; j++)
			board[i][j] = '-';

	srand(time(0));
	i = 0;
	while(i < SIZE)
	{
		temp_rand = rand() % 49 + 1;
		if(check_dup(random_numbers, temp_rand) == 1)
			continue;
		else
			random_numbers[i++] = temp_rand;

	}
	printf("random_numbers: ");
	for(i = 0; i < SIZE; i++)
		printf("%d ", random_numbers[i]);

	printf("\n\n");
	update_board(board, random_numbers);
	print_board(board);

}

int check_dup(int* arr, int num)
{
	int i = 0;

	while(arr[i] != 0)
	{	
		if(arr[i++] == num)
			return 1;
	}
	return 0;
}

void update_board(char board[ROWS][COLUMNS], int arr[])
{
	int row, col, i;	

	for(i = 0; i < SIZE; i++)
	{
		arr[i] -= 1;
		row = arr[i] <= 10 ? 0 : arr[i] / 10;
		col = arr[i] <= 10 ? arr[i] : arr[i] % 10;
		board[row][col] = '+';
	}
}

void print_board(char board[ROWS][COLUMNS])
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
