#include<stdio.h>
#include "hash.h"

int nodeExist(hash* hash, node* runner, void* key, void* value);

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
	newHash->size = size;
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

	printf("location = %d\n", location);

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
		if(nodeExist(hash, runner, key, value))
			return 1;
		while (runner->next != NULL) 
		{
			if(nodeExist(hash, runner, key, value))
				return 1;
			runner = runner->next;
		}
		runner->next = malloc(sizeof(node));
		runner->next->key = key;
		runner->next->value = value;
		runner->next->next = NULL;
		//printf("value = %s\n", (char*)(hash->arr[location]->next->value));
	}

	//printf("return 1\n");
	return 1;
}

int nodeExist(hash* hash, node* runner, void* key, void* value)
{
	return (hash->compFunc(runner->key, key) == 0) &&  (hash->compFunc(runner->value, value) == 0);
}

void* hashfind(hash* hash, void* key)
{
	int bucket = hash->myHashFunc(key) % hash->size;
	node* runner = hash->arr[bucket];

	if(runner == NULL)
		return NULL;

	while(hash->compFunc(runner->key, key) != 0)
		runner = runner->next;

	return runner->value;

}

int destroyHash(hash* hash)
{
	int i;
	node *tempBucket, *currNode, *prevNode;

	for(i = 0; i < hash->size; i++)
	{
		tempBucket = hash->arr[i];
		currNode = tempBucket;
		prevNode = tempBucket;
		while(currNode != NULL)
		{
			free(prevNode);
			prevNode = currNode;
			currNode = currNode->next;
		}
		free(currNode);
	}
	free(hash->arr);
	free(hash);

	return 1;
}
