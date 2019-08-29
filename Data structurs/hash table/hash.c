#include<stdio.h>
#include "hash.h"

int nodeExist(hash* hash, node* runner, void* key, void* value);
void printHash(hash* hash);

int nodeExist(hash* hash, node* runner, void* key, void* value)
{
	return (hash->compFunc(runner->key, key) == 0) && (hash->compFunc(runner->value, value) == 0);
}

void printHash(hash* hash)
{
	int i;
	node* runner;

	for (i = 0; i < hash->size; i++)
	{
		runner = hash->arr[i];
		while (runner)
		{
			printf("[%s, %s] ", (char*)runner->key, (char*)runner->value);
			runner = runner->next;
		}
		printf("\n");
	}
}

hash* createHash(int size, hashFuction1 hashFunc, compareFunction compFunc)
{
	if (hashFunc == NULL || compFunc == NULL || size <= 0)
		return NULL;

	hash* newHash = malloc(sizeof(hash));
	if (newHash == NULL)
		return NULL;
	newHash->arr = calloc(size, sizeof(node*));
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
	node *runner, *currNode;

	if (hash == NULL || key == NULL | value == NULL)
		return 0;

	location = (hash->myHashFunc(key)) % hash->size;

	//printf("location = %d\n", location);

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
		do
		{
			if (nodeExist(hash, runner, key, value))
				return 1;
			currNode = runner;
			runner = runner->next;
		} while (runner != NULL);

		currNode->next = malloc(sizeof(node));
		currNode->next->key = key;
		currNode->next->value = value;
		currNode->next->next = NULL;
		//printf("value = %s\n", (char*)(hash->arr[location]->next->value));
	}

	//printf("return 1\n");
	return 1;
}

void* hashfind(hash* hash, void* key)
{
	int bucket = hash->myHashFunc(key) % hash->size;
	node* runner = hash->arr[bucket];

	if (runner == NULL)
		return NULL;

	while (hash->compFunc(runner->key, key) != 0)
		runner = runner->next;

	return runner->value;

}

int deleteNode(hash* hash, void* key)
{
	int bucket = hash->myHashFunc(key) % hash->size;
	node *runner = hash->arr[bucket], *prevNode;

	if (runner == NULL)
		return 0;

	prevNode = runner;
	while (hash->compFunc(runner->key, key) != 0) 
	{
		prevNode = runner;
		if (runner->next)
			runner = runner->next;
		else
			return 0;
	}

	if (prevNode == runner) /*key is head*/
	{
		if (runner->next)
			hash->arr[bucket] = runner->next;
		else
			hash->arr[bucket] = NULL;
	}
	else if (runner->next == NULL) /*key is tail*/
	{
		prevNode->next = NULL;
	}
	else					/*key is in middle*/
	{
		prevNode->next = runner->next;
	}
	free(runner);
	return 1;
}

int destroyHash(hash* hash)
{
	int i;
	node *tempBucket, *currNode, *prevNode;

	for (i = 0; i < hash->size; i++)
	{
		tempBucket = hash->arr[i];
		currNode = tempBucket;
		prevNode = tempBucket;
		while (currNode != NULL)
		{
			prevNode = NULL;
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

//void hashForEach(hash* hash, userFunc func)
