#include<stdio.h>
#include<stdlib.h>

int* insert(int* num, int* pos, int* capacity, int* arr);

int main()
{
	int capacity, num, index, pos = 0, i;
	int *arr;

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
		insert(&num, &pos, &capacity, arr);
	}
	while(num > 0);
	
	
	for(i = 0; i < pos; i++)
		printf("%d ", arr[i]);

	free(arr);
}

int* insert(int* num, int* pos, int* capacity, int* arr)
{
	
	int* temp;

	if(*num == -1)
		return arr;

	if(*pos >= *capacity)
	{
		temp = realloc(arr, (*capacity) * 2);
		if(temp != NULL)
		{
			arr = temp;
			*capacity *= 2;
		}
		else
			return arr;
	}
	
	arr[*pos] = *num;
	(*pos)++;
	
}
