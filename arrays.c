#include<stdio.h>
#include<stdlib.h>

void sort_one_zero(int* arr);
void bubble_sort(int* arr);
void swap(int* a, int* b);
void sort_odd_even(int *arr);
int most_accure_value(int* arr, int* accurence);

#define SIZE 8

int main()
{
	int i;
	int arr[SIZE] = {0,1,0,1,0};
	int arr2[SIZE];

	printf("please enter 8 numbers\n");

	for(i = 0; i < SIZE; i++)
	{
		scanf("%d", &arr2[i]);
	}

/*	
	sort_one_zero(arr);  
	bubble_sort(arr2);
*/
	sort_odd_even(arr2);

	for(i = 0; i < SIZE; i++)
		{
		printf("%d ", arr2[i]);
		}
	printf("\n");
}

void sort_one_zero(int* arr)
{
	int *left, *right;

	left = &arr[0];
	right = &arr[SIZE - 1];

	while(left < right)
	{
		while(*left != 1) left++;
		while(*right != 0) right --;
		if(left < right) swap(left,right);
	}

}

void swap(int* a, int* b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

void bubble_sort(int* arr)
{
	int i, j, flag = 0;
	
	for(i = 0; i < SIZE - 1; i++)
	{
		flag = 0;
		for(j = 0; j < SIZE - i - 1; j++)
		{
			if(arr[j] > arr[j+1])
			{
				swap(&arr[j], &arr[j+1]);
				flag = 1;
			}
		}
		if(flag == 0) break;	
	}
}

void sort_odd_even(int *arr)
{
	int j, flag = 0;
		
		while(1)
		{
			flag = 0;
			for(j = 0; j < SIZE - 1; j++)
			{
				if((arr[j] % 2) > 0 && (arr[j+1] % 2) == 0)
				{
					swap(&arr[j], &arr[j+1]);
					flag = 1;
				}
			}
			if(flag == 0) break;	
		}
}

int most_accure_value(int* arr, int* accurence)
{

}
	
