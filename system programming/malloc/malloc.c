#include<stdio.h>
#include<stdlib.h>
#include "malloc.h"

int buff_size;

void* memAlloc(void* buffer, unsigned int size)
{
	void* head;
	int noResult = 0, try_insert = 1;
	unsigned int *current, *next;

	buffer = buffer - 4;
	head = buffer;

	while(size % 4 != 0) 
		size++;

	while(1)
	{
		if(IS_OCCUPIED(buffer))
			buffer += *current + 4;

		if(((int*)buffer - (int*)head) >= buff_size)
			break;		

		current = (unsigned int*)buffer;
		next = buffer + *current + 4;
		try_insert = 1;

		while(try_insert)
		{
			if (*current >= size)
			{
				*(unsigned int*)(buffer + size + 4) = *(unsigned int*)buffer - size - 4;
				*(unsigned int*)buffer = size;
				*(unsigned int*)buffer = SET_OCCUPIED(buffer);
				return buffer + 4;
			}
			else
			{
				if(!IS_OCCUPIED(next))
				{
					while(!IS_OCCUPIED(next))
					{
						*current += *next + 4;
						next = buffer + *current + 4;
					}
				}
				else
				{
					try_insert = 0;
					buffer += *current + 4;
				}

			}
		}
	}

	return NULL;

/*
	while((*(unsigned int*)buffer & 0x7fffffff) < size || IS_OCCUPIED(buffer)) //HEADER_VALUE(buffer)
	{
		if(buffer - head > buff_size)
		{
			noResult = 1;
			break;
		}
		//printf("add %u\n", *(unsigned int*)buffer & 0x7fffffff);
		buffer += (*(unsigned int*)buffer & 0x7fffffff) + 4;
	}

	if(noResult == 1)
	{
		return NULL;
	}
*/	

}

void* memInit(void* buffer, unsigned int size)
{
	int* header;

	//printf("buffer = %u\n", temp);
	//printf("buffer / 4 = %u\n", temp / 4);

	while((unsigned int)buffer & 3 != 0)
	{
		buffer++;
		size--;
	}

	while(size % 4 != 0)
		size--;

	buff_size = size;
	header = (unsigned int*)buffer;
	*header = size;
	SET_FREE(header);

	return buffer + 4;
}
