#include<stdio.h>
#include<stdlib.h>
#include "darray_int.h"

struct darray {
	int *arr;
	int index;
	int capacity;
	int initial_capacity;
};

AdtStatus darrayCreate(darray **dArr, size_t initial_capacity)
{
	darray *tempArr;
	tempArr = malloc(sizeof(darray*));

	if (tempArr)
	{
		tempArr->index = 0;
		tempArr->capacity = initial_capacity;
		tempArr->initial_capacity = initial_capacity;
		tempArr->arr = malloc(initial_capacity * sizeof(int));
		if (tempArr->arr)
		{
			*dArr = tempArr;
			return OK;
		}

	}
	return AllocationError;
}
/* Add number to the end. */
darray* darrayAdd(darray *dArr, int  _item)
{
	int* temp;

	if (dArr == NULL)
	{
		return NULL;
	}

	if (dArr->index >= dArr->capacity)
	{
		temp = realloc(dArr->arr, dArr->capacity * 2);
		if (temp != NULL)
		{
			dArr->arr = temp;
			dArr->capacity *= 2;
		}
		else
		{
			return NULL;
		}
	}
	dArr->arr[dArr->index] = _item;
	dArr->index++;
	return dArr;
}

AdtStatus darrayDelete(darray *dArr, int* _item)
{
	int * temp;

	if (dArr == NULL)
		return AllocationError;

	if (dArr->arr == NULL)
		return AllocationError;

	temp = dArr->arr;
	
	if (dArr->capacity > dArr->initial_capacity && dArr->index <= (size_t)(0.75*((dArr->capacity / 2))))
	{
		temp = realloc(temp, ((dArr->capacity) / 2) * sizeof(int));
	}
	if (temp != NULL)
	{
		dArr->arr = temp;
		dArr->capacity = dArr->capacity / 2;
	}
	else
	{
		return AllocationError;
	}

	*_item = dArr->arr[dArr->index - 1];
	dArr->index--;
	return OK;
}

AdtStatus   darrayGet(darray *dArr, size_t _index, int *_item)
{
	if (dArr == NULL || _index < 0 || _index >= dArr->index || _item == NULL)
		return AllocationError;

	*_item = dArr->arr[_index];
	return OK;
}

AdtStatus darraySet(darray *dArr, size_t _index, int  _item)
{
	if (dArr == NULL || _index < 0 || _index > dArr->index || _item == NULL)
		return AllocationError;

	dArr->arr[_index] = _item;
	return OK;
}

int   darrayItemsNum(darray *dArr, int*  _numOfItems)
{
	if (dArr == NULL || _numOfItems == NULL)
		return AllocationError;

	*_numOfItems = dArr->index;
	return OK;
}

AdtStatus darraySort(darray *dArr)
{
	int i, j;
	int temp;
	size_t arraySize = dArr->index;

	if (dArr == NULL || arraySize <= 0)
		return AllocationError;

	for (i = 0; i < arraySize - 1; i++)
	{
		for (j = 0; j < arraySize - i - 1; j++)
		{
			if (dArr->arr[j] > dArr->arr[j + 1])
			{
				temp = dArr->arr[j];
				dArr->arr[j] = dArr->arr[j + 1];
				dArr->arr[j + 1] = temp;
			}
		}
	}
	return OK;
}

void print_AD(darray *dArr)
{
	int i;

	if (dArr == NULL)
	{
		return;
	}

	for (i = 0; i < dArr->index; i++)
		printf("%d ", dArr->arr[i]);

	printf("\n");
}

AdtStatus darrayDestroy(darray *dArr)
{
	if (dArr == NULL) {
		return AllocationError;
	}
	if (dArr->arr != NULL) {
		free(dArr->arr);
	}

	free(dArr);

	return OK;
}

