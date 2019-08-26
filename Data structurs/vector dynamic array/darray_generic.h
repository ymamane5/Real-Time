#ifndef H_DARRAY
#define H_DARRAY
#include <stdlib.h>

typedef enum { OK, AllocationError } AdtStatus;

/* forward declaration of the darray type */
typedef struct darray darray;
typedef struct vector vector;

struct darray {
	void **arr;
	int index;
	int capacity;
	int initial_capacity;
};

struct vector {
	int x;
	int y;
};

typedef void(*elementDestroy)(void *_elem, void *context);
typedef int(*elementCompare)(void *_elemA, void *_elemB);

/* Create a new dynamic array. Return its address in d_arr.
   The initial capacity is the number of items that can be stored
   before a new allocation is needed. */
AdtStatus darrayCreate(darray **dArr, size_t initial_capacity);
AdtStatus darrayDestroy(darray *dArr, elementDestroy destroyFunc, void *context);

/* Add number to the end. */
AdtStatus   darrayAdd(darray *dArr, void  *_item);

/* Delete number from the end, hand-over the deleted item
   in a variable pointed to by _item */
AdtStatus   darrayDelete(darray *dArr, void **_item);

AdtStatus   darrayGet(darray *dArr, size_t _index, void **_item);
AdtStatus   darraySet(darray *dArr, size_t _index, void  *_item);
AdtStatus   darrayItemsNum(darray *dArr, int*  _numOfItems);
void printVector(void* elem);

/* in place (ascending) sorting an array of size arraySize */
AdtStatus darraySort(darray *dArr, elementCompare compareFunc); /* correct this !!! */
int vectorsCompare(void* _elemA, void* _elemB);
#endif