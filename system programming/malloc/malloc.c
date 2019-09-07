#include<stdio.h>
#include<stdlib.h>
#include "malloc.h"

int buff_size;

void* memFree(void* buffer, void* address)
{
	void *current, *next;
	
	current = address;
	next = current + HEADER_VALUE(current) + 4;

	printf("freeing block %d\n", HEADER_VALUE(current));
	*(unsigned int*)(current - 4) = SET_FREE(current);
	
	printf("next[%p] = %d  IS_OCCUPIED(next) = %d", next, HEADER_VALUE(next), IS_OCCUPIED(next));

	//printf("next - head = %d\n", next - buffer);
	while(!IS_OCCUPIED(next) && ((char*)next - (char*)buffer < buff_size)) // is free
	{
		//printf("unifying during free\n");
		*(unsigned int*)(current - 4) += HEADER_VALUE(next) + 4;
		next = current + HEADER_VALUE(current) + 4;
	}

	//printf("after unify: %u\n", HEADER_VALUE(current));

	return address;
}

void* memAlloc(void* buffer, unsigned int size)
{
	void *head, *current, *next;
	int noResult = 0, try_insert = 1, i=0;

	//printf("**in memAlloc**\n");
	head = buffer;

	while(size % 4 != 0) 
		size++;

	current = buffer;
	next = current + HEADER_VALUE(current) + 4;
	
	while(1)
	{
		//printf("next - head = %d\n", ((char*)next - (char*)head));
		if(((char*)next - (char*)head) > buff_size + 1)
			break;
		
		while(IS_OCCUPIED(current)){	
			//printf("current = %d   next = %d\n",HEADER_VALUE(current), HEADER_VALUE(next));
			current += HEADER_VALUE(current) + 4;
			next = next + HEADER_VALUE(next) + 4;
			//printf("(while) next[%p] - head[%p] = %d\n", next, head, ((char*)next - (char*)head));
			if(((char*)next - (char*)head) > buff_size + 1)
				break;
		}
		
		if(((char*)next - (char*)head) > buff_size + 1)
			break;
		
		try_insert = 1;
		while(try_insert)
		{
			//printf("IS_OCCUPIED(current) = %d\n", IS_OCCUPIED(current));
			if(IS_OCCUPIED(current))
			{
				try_insert = 0;
				break;
			}
			
			if (HEADER_VALUE(current) >= size)  // block is big enough
			{
				printf("allocating %d to block %d\n", size, HEADER_VALUE(current));
				*(unsigned int*)(current + size) = HEADER_VALUE(current) - size - 4;
				*(unsigned int*)(current - 4)= size;
				*(unsigned int*)(current - 4) = SET_OCCUPIED(current);
			//	printf("aloocated: block = %p   value = %u\n", current, HEADER_VALUE(current));
			//	printf("next = %d\n", HEADER_VALUE(HEADER_VALUE(current) + current + 4));
				return current;
			}
			else // try to unify free blocks
			{
				if(!IS_OCCUPIED(next) && ((char*)next - (char*)current < buff_size))
				{
					while(!IS_OCCUPIED(next) && ((char*)next - (char*)current < buff_size))
					{
						//printf("unifying\n");
						*(unsigned int*)(current - 4) += *(unsigned int*)next + 4;
						next = next + HEADER_VALUE(next) + 4;
						//i++;
						
						if((char*)next - (char*)head > buff_size + 1)
							return NULL;
					}		
				}
				else
				{
					if((char*)next - (char*)head > buff_size + 1)
							return NULL;
					try_insert = 0;
					current += HEADER_VALUE(current) + 4;
					next = next + HEADER_VALUE(next) + 4;
				}

			}
		}
	}

	return NULL;

}

void* memInit(void* buffer, unsigned int size)
{
	int* header;

	while((unsigned int)buffer & 3 != 0)
	{
		buffer++;
		size--;
	}

	while(size % 4 != 0)
		size--;

	buff_size = size;
	header = (unsigned int*)buffer;
	*header = size - 4;
	SET_FREE(header);
	
	printf("buffsize = %d\n", *header);

	return buffer + 4;
}
