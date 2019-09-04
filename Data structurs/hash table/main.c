#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include "hash.h"

#define HASH_SIZE 5

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
	//char* str = "abcd";
	//char* str2 = "abcde";
	hash* myHash = createHash(HASH_SIZE, hashFunc, copareFunc);
	
	if (myHash == NULL)
	{
		printf("cannot create hash table\n");
		exit(0);
	}

	insert_test(myHash);
	destroyHash(myHash);
}

void insert_test(hash* myHash)
{
	insert(myHash, "key1", "value1");
	insert(myHash, "key2", "value2");
	insert(myHash, "key3", "value3");
	insert(myHash, "key4", "value4");
	insert(myHash, "key5", "value5");
	insert(myHash, "key6", "value6");
	insert(myHash, "key7", "value7");
	insert(myHash, "key8", "value8");
	insert(myHash, "key9", "value9");
	insert(myHash, "key10", "value10");
	insert(myHash, "key11", "value11");
	insert(myHash, "key12", "value12");
	printHash(myHash);
	printf("***********************************\n");
	deleteNode(myHash, "key6");
	printHash(myHash);
}
