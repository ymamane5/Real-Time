//#include <stdlib.h>
//#include <stdio.h>

#ifndef H_DARRAY
#define H_DARRAY

typedef enum { OK, AllocationError }AdtStatus;
/* forward declaration of the darray type */
typedef struct darray darray;
/* Create a new dynamic array. Return its address in d_arr.
   The initial capacity is the number of items that can be stored
   before a new allocation is needed. */
AdtStatus darrayCreate(darray **dArr, size_t initial_capacity);
AdtStatus darrayDestroy(darray *dArr);
/* Add number to the end. */
darray*   darrayAdd(darray *dArr, int  _item);
/* Delete number from the end. */
AdtStatus   darrayDelete(darray *dArr, int* _item);
AdtStatus   darrayGet(darray *dArr, size_t _index, int *_item);
AdtStatus   darraySet(darray *dArr, size_t _index, int  _item);
int   darrayItemsNum(darray *dArr, int*  _numOfItems);
/* in place (ascending) sorting an array of size arraySize */
AdtStatus darraySort(darray *dArr);
void print_AD(darray *dArr);

#endif