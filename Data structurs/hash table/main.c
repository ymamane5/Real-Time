#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include "hash.h"

int main()
{

	char* str = "abcd", str2 = "abcde";
	hash* myHash = createHash(20, hashFunc, copareFunc);
	if (myHash != NULL)
		printf("hash table created\n");
	else {
		printf("cannot create hash table\n");
		getch();
		exit(0);
	}
	insert(myHash, str, "value1");
	insert(myHash, str2, "value1");

	//printf("%s\n", hashptr->arr[]->value);
//	int loc = myHash->myHashFunc(str);
//	printf("%s", myHash->arr[loc]->value);

	getch();
}

int hashFunc(unsigned char* str)
{
	unsigned int hash = 0;
	int c;

	while (c = *str++)
		hash += c;

	return hash;
}

int copareFunc(void* elem1, void* elem2)
{
	char* str1 = *(char**)elem1;
	char* str2 = *(char**)elem2;
	
	return strcmp(str1, str2);
}
