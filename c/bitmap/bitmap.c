#include<stdio.h>
#include<stdlib.h>
#include "bitmap.h"


Bitmap* createBitmap(int size)
{
	Bitmap* temp = (Bitmap*)malloc(sizeof(Bitmap));
	int sizeUp = size / 8;

	if (size < 0)
	{
		printf("please enter positive number\n");
		return NULL;
	}

	if (temp == NULL)
		return NULL;

	if ((size % 8) > 0)
	{
		sizeUp = size / 8 + 1;
	}
	temp->m_arr = calloc(sizeUp, sizeof(char));
	if (temp->m_arr == NULL)
	{
		free(temp);
		return NULL;
	}

	temp->m_size = size;
	return temp;
}

void destroyBitmap(Bitmap* map)
{
	free(map->m_arr);
	free(map);
}

int bitOn(Bitmap* map, int location)
{
	int offset = location % 8, byteNum = location / 8;
	unsigned char mask = 1;
	
	if (location < 0 || location > map->m_size)
	{
		return 0;
	}
	mask <<= offset;

	map->m_arr[byteNum] = map->m_arr[byteNum] | mask;

	return 1;
}

int bitOff(Bitmap* map, int location)
{
	int offset = location % 8, byteNum = location / 8;
	unsigned char mask = 1;

	if (location < 0 || location > map->m_size)
	{
		return 0;
	}
	mask <<= offset;
	mask = ~mask;

	map->m_arr[byteNum] = map->m_arr[byteNum] & mask;

	return 1;
}

int isBit(Bitmap* map, int location)
{
	int offset = location % 8, byteNum = location / 8;
	unsigned char mask = 1;

	if (location < 0 || location > map->m_size)
	{
		return -1;
	}
	mask <<= offset;
	return (map->m_arr[byteNum] & mask) > 0 ? 1 : 0;
}

void printBitmap(Bitmap* map)
{
	int i, j, mask = 1;
	char chPrint;

	for (i = 0; i < map->m_size / 8; i++)
	{
		for (j = 0; j < 8; j++)
		{
			printf("%c", (map->m_arr[i] & mask) > 0 ? '1' : '0');
			mask <<= 1;
		}
		printf("  ");
		mask = 1;
	}
	for (j = 0; j < map->m_size % 8; j++)
		{
			printf("%c", (map->m_arr[i] & mask) > 0 ? '1' : '0');
			mask <<= 1;
		}
	printf("\n");
}
