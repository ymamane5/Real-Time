#include<stdio.h>
#include<stdlib.h>
#include "malloc.h"

int buff_size;

void* memFree(void* buffer, void* address)
{
	void *current, *next;
	int i = 0;
	
	current = address;
	next = current + HEADER_VALUE(current) + 4;

	printf("***memFree***\n");
	*(unsigned int*)(current - 4) = SET_FREE(current);

	while(!IS_OCCUPIED(next) && i < 10) // is free
	{
		printf("next = %p\n", next);
		printf("unifing %u\n", HEADER_VALUE(current));
		printf("HEADER_VALUE(next) = %u\n", HEADER_VALUE(next));
		*(unsigned int*)(current - 4) += HEADER_VALUE(next) + 4;
		next = current + HEADER_VALUE(current) + 4;
		i++;
	}

	printf("after unify: %u\n", HEADER_VALUE(current));

	return address;
}

void* memAlloc(void* buffer, unsigned int size)
{
	void *head, *current, *next;
	int noResult = 0, try_insert = 1;

	buffer = buffer;
	head = buffer;

	while(size % 4 != 0) 
		size++;

	while(1)
	{
		//printf("go to while\n");
		while(IS_OCCUPIED(buffer)){
			//printf("add %u\n", (*(unsigned int*)buffer & 0x7fffffff) + 4);
			buffer += HEADER_VALUE(buffer) + 4;
			//printf("buffer = %p\n", buffer);
			//printf("*buffer = %u\n", *(unsigned int*)buffer);
		}

		//printf("buffer - head = %d\n", (char*)buffer - (char*)head);
		if(((char*)buffer - (char*)head) >= buff_size)
			break;		

		current = buffer;
		next = buffer + HEADER_VALUE(current) + 4;
		try_insert = 1;

		while(try_insert)
		{
			if (HEADER_VALUE(current) >= size)
			{
				printf("allocating mem\n");
				*(unsigned int*)(buffer + size) = HEADER_VALUE(buffer) - size - 4;
				*(unsigned int*)(buffer - 4)= size;
				*(unsigned int*)(buffer - 4) = SET_OCCUPIED(buffer);
				printf("aloocated: block = %p   value = %u\n", buffer, HEADER_VALUE(buffer));
				return buffer;
			}
			else
			{
				if(!IS_OCCUPIED(next))
				{
					while(!IS_OCCUPIED(next))
					{
						*(unsigned int*)(current - 4) += *(unsigned int*)next + 4;
						next = buffer + HEADER_VALUE(current) + 4;
					}
				}
				else
				{
					try_insert = 0;
					buffer += HEADER_VALUE(current) + 4;
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
