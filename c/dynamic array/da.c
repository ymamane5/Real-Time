#include<stdio.h>
#include "da.h"

void create_DA(int capacity)
{
	DA *da = malloc(sizeof(DA));
	da->capacity = capacity;
	da->index = 0;
	da->arr = malloc(sizeof(int) * capacity);
}

void printDA(DA *da) { return; }

int insert(DA *da, int num) { return num; }

void destroy(DA *da) { return; }
