#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "darray_generic.h"


int vectorsCompare(void* _elemA, void* _elemB)
{
	int leng1, leng2;
	vector* vector1 = (vector*)_elemA;
	vector* vector2 = (vector*)_elemB;

	leng1 = vector1->x + vector1->y;
	leng2 = vector2->x + vector2->y;

	return leng1 - leng2;
}

void destroyVector(void *_elem, void *context)
{
	if (_elem != NULL)
	{
		vector* vectorElem = (vector*)_elem;//struct
		if (context != NULL)
		{
			FILE *file = (FILE *)context;
			fprintf(file, "%d %d", vectorElem->x, vectorElem->y);
			free(vectorElem);
		}
	}
}

AdtStatus darrayCreate(darray **dArr, size_t initial_capacity)
{
	darray *tempArr;
	tempArr = malloc(sizeof(darray*));

	if (tempArr)
	{
		tempArr->index = 0;
		tempArr->capacity = initial_capacity;
		tempArr->initial_capacity = initial_capacity;
		tempArr->arr = malloc(initial_capacity * sizeof(vector));
		if (tempArr->arr)
		{
			*dArr = tempArr;
			return OK;
		}

	}
	return AllocationError;
}

AdtStatus darrayAdd(darray *dArr, void  *_item)
{
	void* temp;

	if (dArr == NULL || _item == NULL)
	{
		return AllocationError;
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
			return AllocationError;
		}
	}
	vector* vec = malloc(sizeof(vector));
	*vec = *(vector*)_item;
	dArr->arr[dArr->index] = (vector*)vec;
	dArr->index++;
	return OK;
}

AdtStatus darrayDelete(darray *dArr, void** _item)
{
	void** temp;

	if (dArr == NULL)
		return AllocationError;

	if (dArr->arr == NULL)
		return AllocationError;

	temp = dArr->arr;

	if (dArr->capacity > dArr->initial_capacity && dArr->index <= (size_t)(0.75*((dArr->capacity / 2))))
	{
		temp = realloc(temp, ((dArr->capacity) / 2) * sizeof(vector));
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

AdtStatus   darrayGet(darray *dArr, size_t _index, void**_item)
{
	if (dArr == NULL || _index < 0 || _index >= dArr->index || _item == NULL)
		return AllocationError;

	*_item = dArr->arr[_index];
	return OK;
}

AdtStatus darraySet(darray *dArr, size_t _index, void* _item)
{
	if (dArr == NULL || _index < 0 || _index > dArr->index || _item == NULL)
		return AllocationError;

	dArr->arr[_index] = _item;
	return OK;
}

int darrayItemsNum(darray *dArr, int*  _numOfItems)
{
	if (dArr == NULL || _numOfItems == NULL)
		return AllocationError;

	*_numOfItems = dArr->index;
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
		printVector(dArr->arr[i]);

	printf("\n");
}

void printVector(void* elem)
{
	vector v = *((vector*)elem);
	
	printf("(%d, %d) ", v.x, v.y);
}

AdtStatus darraySort(darray *dArr, elementCompare compareFunc)
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
			if (compareFunc(dArr->arr[j] , dArr->arr[j + 1]) > 0)
			{
				temp = dArr->arr[j];
				dArr->arr[j] = dArr->arr[j + 1];
				dArr->arr[j + 1] = temp;
			}
		}
	}
	return OK;
}

AdtStatus darrayDestroy(darray *dArr, elementDestroy destroyFunc, void *context)
{
	int i = 0;

	if (dArr)
	{
		if (dArr->arr)
		{
			for (i; i < dArr->index; i++)
			{
				destroyFunc(dArr->arr[i], context);
			}
			free(dArr->arr);
		}
		free(dArr);
		return OK;
	}
	return AllocationError;
}

