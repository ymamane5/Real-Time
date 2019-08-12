#include<stdio.h>
#include<stdlib.h>
#include "da.h"

DA* create_DA(int capacity)
{
	DA *da = malloc(sizeof(DA));
	if(da == NULL)
		return NULL;
	da->capacity = capacity;
	da->index = 0;
	da->arr = malloc(sizeof(int) * capacity);
	if(da->arr == NULL)
	{
		free(da);
		return NULL;
	}

	return da;
}

void printDA(DA* da) 
{ 
	int i;

	if(da == NULL)
		return;

	for (i = 0; i < da->index; i++)
		printf("%d ", da->arr[i]);
}

int insert(DA *da, int num) 
{ 
	int* temp;

	if (num == -1 || da == NULL)
		return 0;

	if (da->index >= da->capacity)
	{
		temp = realloc(da->arr, da->capacity * 2);
		if (temp != NULL)
		{
			da->arr = temp;
			da->capacity *= 2;
		}
		else
			return 0;
		
	}
	da->arr[da->index] = num;
	da->index++;
	return 1;
}

void destroy(DA *da) 
{
	free(da->arr);
	free(da); 
}
