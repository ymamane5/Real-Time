#include<stdio.h>
#include "malloc.h"

#define BUFF_MAX 255

int main()
{
	void* buffer_arr[BUFF_MAX] = {0};
	void* buffer = memInit(buffer_arr, BUFF_MAX);
	printf("buffer address = %p\n", buffer - 4);

	void* myBlock1 = memAlloc(buffer, 30);
	void* myBlock2 = memAlloc(buffer, 70);
	void* myBlock3 = memAlloc(buffer, 15);
	void* myBlock4;

	memFree(buffer, myBlock2);
	memFree(buffer, myBlock3);
	myBlock2 = memAlloc(buffer, 103);
	myBlock4 = memAlloc(buffer, 100);

	printf("myBlock1 address = %p\nmyBlock1 size = %u\n", myBlock1, HEADER_VALUE(myBlock1));
	printf("myBlock2 address = %p\nmyBlock2 size = %u\n", myBlock2, HEADER_VALUE(myBlock2));
	printf("myBlock3 address = %p\nmyBlock3 size = %u\n", myBlock3, HEADER_VALUE(myBlock3));
	printf("myBlock4 = %p\n", myBlock4);
	
	//printf("next pos = %d\n", HEADER_VALUE(myBlock3 + HEADER_VALUE(myBlock3) + 4));

}
