#include<stdio.h>
#include<stdlib.h>
#include "bits.h"

unsigned char* rotateN(unsigned char x, int n)
{
	int temp, i;
	unsigned char mask = 1;
	unsigned char* y;

	if(n < 0)
		return NULL;

	y = malloc(sizeof(char));
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
	y = malloc(sizeof(char));

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

int setbits(char* x, int p, int n, char y)
{
	unsigned char mask = 0xFF;

	if(x == NULL || p < 1 || p > 8 || n < 0 || n > 8)
		return 0;

	mask <<= n;	
	y = y & (~mask);

	while(p > n)
	{
		y <<= 1;
		mask <<= 1;
		mask++;
		p--;
	}

	*x = *x & mask;
	*x = *x | y;	

	return 1;
}

int setbits2(int w, int i, int j, int value)
{
	unsigned int mask = 0xFFFFFFFF;
	int k;

	if (i < j || w < 0 || i < 0 || i > 31 || j < 0 || j > 31 || value < 0 || value > 1)
		return 0;

	mask <<= (i - j + 1);

	for (k = 0; k < j; k++)
	{
		mask <<= 1;
		mask++;
	}

	if (value == 0)
		w = w & mask;
	else if (value == 1)
		w = w | (~mask);
	else
		return 0;

	return w;
}

void int2bin(unsigned int n)
{
	char arr[33];
	int i;

	for(i = 0; i<32; i++)
		arr[i] = '0';

	for(i = 31; n > 0; i--, n /= 2)
	{
		arr[i] = (n % 2 == 0) ? '0' : '1';
	}

	for(i = 0; arr[i] == '0'; i++);

	while(i < 32){
		printf("%c", arr[i]);
		i++;
	}

	printf("\n");		

}
