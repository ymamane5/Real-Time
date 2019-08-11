#include<stdio.h>
#include<stdlib.h>

int* insert(int* num, int* pos, int* capacity, int* arr);

int main()
{
	int capacity, num, index, i = 0;
	int *p, *arr;

	printf("please enter array size:\n");
	scanf("%d", &capacity);
	
	while(capacity <= 0)
	{
	printf("please enter positive number\n");
	scanf("%d", &capacity);
	}

	arr = malloc(sizeof(int) * capacity);

	printf("please enter numbers\n");
	do{
		scanf("%d", &num);
		insert(&num, &i, &capacity, arr);
	}
	while(num > 0);
	
	
	for(i = 0; i < capacity; i++)
		printf("%d ", arr[i]);

}

int* insert(int* num, int* pos, int* capacity, int* arr)
{
	
	int* temp;

	if(*pos >= *capacity)
	{
		temp = realloc(arr, (*capacity) + 1);
		if(temp != NULL)
		{
			arr = temp;
			(*capacity)++;
		}
	}
	
	arr[*pos] = *num;
	(*pos)++;
	
}
