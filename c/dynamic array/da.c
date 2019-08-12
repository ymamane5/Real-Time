#include<stdio.h>
#include "da.h"

DA* create_DA(int capacity)
{
	DA *da = malloc(sizeof(DA));
	da->capacity = capacity;
	da->index = 0;
	da->arr = malloc(sizeof(int) * capacity);

	return da;
}

void printDA(DA* da) { return; }

int insert(DA *da, int num) 
{ 
	int* temp;

	if (num == -1)
		return 0;

	if (da->index >= da->capacity)
	{
		da->arr = realloc(da->arr, (da->capacity) * 2);
		da->capacity *= 2;
		/*
		temp = realloc(da->arr, da->capacity * 2);
		if (temp != NULL)
		{
			da->arr = temp;
			da->capacity *= 2;
		}
		else
			return 0;
		*/
	}

	da->arr[da->index] = num;
	da->index++;
	return 1;

}

void destroy(DA *da) { free(da); }
