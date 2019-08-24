#include<stdio.h>
#include<stdlib.h>
#include "bits.h"

unsigned char* rotateN(unsigned char x, int n)
{
	int temp, i;
	unsigned char mask = 1;
	unsigned char* y;
	y = malloc(1, sizeof(char));
	*y = x;

	for (i = 0; i < n; i++)
	{
		temp = *y & mask;
		*y >>= 1;
		if (temp > 0)
			*y = *y | 128;
	}
	return y;
}

unsigned char* invertChar(unsigned char x)
{
	unsigned char* y;
	y = malloc(1, sizeof(char));

	*y = ~x;
	return y;
}

void char2bin(unsigned char x)
{
	int i;
	unsigned char mask = 128;

	for (i = 0; i < 8; i++)
	{
		printf("%c ", (x & mask) > 0 ? '1' : '0');
		mask >>= 1;
	}
	printf("\n");
}
