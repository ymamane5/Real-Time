#include<stdio.h>
#include "hash.h"

hash* createHash(int size, hashFuction1 hashFunc, compareFunction compFunc)
{
	if (hashFunc == NULL || compFunc == NULL || size <= 0)
		return NULL;

	hash* newHash = malloc(sizeof(hash));
	if (newHash == NULL)
		return NULL;
	newHash->arr = malloc(sizeof(node*) * size);
	if (newHash->arr == NULL)
	{
		free(newHash);
		return NULL;
	}
	newHash->myHashFunc = hashFunc;
	newHash->compFunc = compFunc;

	return newHash;

}

int insert(hash* hash, void* key, void* value)
{
	int location;
	node* runner;

	if (hash == NULL || key == NULL | value == NULL)
		return 0;

	location = (hash->myHashFunc(key)) % hash->size;

	if (hash->arr[location] == NULL)
	{
		hash->arr[location] = malloc(sizeof(node));
		hash->arr[location]->key = key;
		hash->arr[location]->value = value;
		hash->arr[location]->next = NULL;
	}
	else
	{
		runner = hash->arr[location];
		while (runner->next != NULL) {
			runner = runner->next;
		}
		runner->next = malloc(sizeof(node));
		runner->next->key = key;
		runner->next->value = value;
		runner->next->next = NULL;
	}

	return 1;
}