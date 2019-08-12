#include<stdio.h>
#include<stdlib.h>

void create_DA(int capacity);

int main()
{

}
/*
files:
da_main.c
da.c
da.h
*/


// if first malloc succeed and the other failed
//in da.c:

void create_DA(int capacity)
{
	DA *da = malloc(sizeof(array));
	da->capacity = capacity;
	da->index = 0;
	da->arr = malloc(sizeof(int) * capacity);
}

void printDA(DA *da){}

int insert(DA *da, int num){}

void destroy(DA *da){}