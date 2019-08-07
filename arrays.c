#include<stdio.h>
#include<stdlib.h>

void sort_one_zero(int* arr);
void swap(int* a, int* b);

#define SIZE 5

int main()
{
int i;
int arr[SIZE] = {0,1,0,1,0};

sort_one_zero(arr);

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
