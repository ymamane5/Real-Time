#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include "hash.h"

void insert_test(hash* myHash);

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
	return strcmp((char*)elem1, (char*)elem2);
}

int main()
{
	char* str = "abcd";
	char* str2 = "abcde";
	hash* myHash = createHash(10, hashFunc, copareFunc);
	if (myHash == NULL)
	{
		printf("cannot create hash table\n");
		exit(0);
	}

	insert_test(myHash);

	//printf("found: %s\n", (char*)hashfind(myHash, "key7"));
	
}

void insert_test(hash* myHash)
{
	char* str = "abcd";
	char* str2 = "abcde";
	
	insert(myHash, str, "value1");
	insert(myHash, str2, "value2");
	insert(myHash, "key3", "value3");
	insert(myHash, "key4", "value4");
	insert(myHash, "key5", "value5");
	insert(myHash, "key6", "value6");
	insert(myHash, "key7", "value7");
	insert(myHash, "key7", "value7");


	printf("hash->arr[4]->key = %s\n", (char*)myHash->arr[4]->key);
	printf("hash->arr[4-2]->key = %s\n", (char*)myHash->arr[4]->next->key);
	printf("hash->arr[4-3]->key = %s\n", (char*)myHash->arr[4]->next->next->key);

	//printf("myHash->arr[3]->value = %s\n", (char*)(myHash->arr[3]->value));
	//printf("myHash->arr[4]->value = %s\n", (char*)(myHash->arr[4]->value));
	//printf("myHash->arr[4(2)]->value = %s\n", (char*)(myHash->arr[4]->next->value));
}





