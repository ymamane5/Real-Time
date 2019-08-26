#include<stdio.h>
#include<stdlib.h>
#include "darray_int.h"

int main()
{
	darray *myDarr;
	int myInt;
	int res;
	int numOfItems;
	AdtStatus tmp;
	tmp = darrayCreate(&myDarr, 100);
	printf("result of create is :%d\n", tmp);

	myDarr = darrayAdd(myDarr, 8);
	myDarr = darrayAdd(myDarr, 10);
	myDarr = darrayAdd(myDarr, 81);
	myDarr = darrayAdd(myDarr, 82);
	print_AD(myDarr);
	darrayDelete(myDarr, &myInt);
	printf("item %d deleted\n", myInt);
	print_AD(myDarr);
	darraySet(myDarr, 2, 3);
	print_AD(myDarr);
	darraySort(myDarr);
	print_AD(myDarr);
	getch();

}





