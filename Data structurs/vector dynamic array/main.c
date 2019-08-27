#include<stdio.h>
#include<stdlib.h>
#include "darray_generic.h"

int main()
{
	AdtStatus tmp;
	char filename[] = "vector.txt";
	int length;
	darray* myDarr;

	vector *vec = malloc(sizeof(vector));
	FILE * file = fopen(filename, "w");
	//elementCompare compFunc = &vectorsCompare;

	tmp = darrayCreate(&myDarr, 100);

	vec->x = 5;
	vec->y = 5;

	darrayAdd(myDarr, vec);

	vec->x = 2;
	vec->y = 7;

	darrayAdd(myDarr, vec);

	vec->x = 10;
	vec->y = 9;

	darrayAdd(myDarr, vec);
	print_AD(myDarr);
	darraySort(myDarr, &vectorsCompare);
	print_AD(myDarr);

}
