#include<stdio.h>
#include<stdlib.h>
#include<math.h>

void sort_one_zero(int* arr);
void bubble_sort(int* arr);
void swap(int* a, int* b);
void sort_odd_even(int *arr);
int most_accure_value(int* arr);
void print_array(int* arr);

#define SIZE 5

int main()
{
	int i, accurence;
	int arr[SIZE] = {0,1,0,1,0};
	int arr2[SIZE];

	printf("please enter 5 numbers\n");

	for(i = 0; i < SIZE; i++)
	{
		scanf("%d", &arr2[i]);
	}

/*	
	sort_one_zero(arr);  
*/
	bubble_sort(arr2);
	printf("sorted array:  ");
	print_array(arr2);
	sort_odd_even(arr2);
	printf("\nsort_odd_even:  ");
	print_array(arr2);
	printf("\nmost_accure_value = %d\n", most_accure_value(arr2));

}

void print_array(int* arr)
{
	int i;

	for(i = 0; i < SIZE; i++)
		{
		printf("%d ", arr[i]);
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
	int i, j, flag = 0;
		
		for(i = 0; i < SIZE; i++)
		{
			flag = 0;
			for(j = 0; j < SIZE - i - 1; j++)
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

int most_accure_value(int* arr)
{
	int i, j ,temp_accurence = 1, max_accurence = 1, temp_num, max_num;

	bubble_sort(arr);

	for(i = 0; i < SIZE; i++)
	{
		temp_num = arr[i];
		for(j = i + 1; j < SIZE; j++)
		{
			if(arr[i] == temp_num)
				temp_accurence++;
		}
		if(temp_accurence > max_accurence)
		{
			max_accurence = temp_accurence;
			max_num = temp_num;
		}
		temp_accurence = 1;		
	}
		
	return max_num;
}
	
