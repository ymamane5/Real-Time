#include<stdio.h>
#include "malloc.h"

#define BUFF_MAX 256

int main()
{
	void* buffer_arr[BUFF_MAX] = {0};
	void* buffer = memInit(buffer_arr, BUFF_MAX);
	printf("buffer address = %p\n", buffer);

	void* myBlock1 = memAlloc(buffer, 30);
	printf("myBlock1 address = %p\nmyBlock1 size = %u\n", myBlock1, *(unsigned int*)(myBlock1-4) & 0x7fffffff);
	void* myBlock2 = memAlloc(buffer, 70);

	printf("myBlock2 address = %p\nmyBlock2 size = %u\n", myBlock2, *(unsigned int*)(myBlock2-4) & 0x7fffffff);
	printf("3rd pos = %d\n", *(unsigned int*)(myBlock2 + 72));

}