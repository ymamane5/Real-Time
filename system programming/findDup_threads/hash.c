#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include "hash.h"
#include "findDup.h"

void printHash(hash* hash)
{
	int i;
	node* runner;

	for (i = 0; i < hash->size; i++)
	{
		runner = hash->arr[i];
		if(runner == NULL)
			continue;

		while (runner)
		{
			md5Print((char*)runner->key);
			printf("%20s", (char*)runner->value);
			runner = runner->next;
		}
		printf("\n");
	}
}

hash* createHash(int size, hashFuction1 hashFunc, compareFunction compFunc)
{
	if(hashFunc == NULL || compFunc == NULL || size <= 0)
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
	//newHash->locks = malloc(sizeof(pthread_mutex_t) * (size / 100));
	newHash->size = size;
	newHash->myHashFunc = hashFunc;
	newHash->compFunc = compFunc;

	return newHash;

}

int insert(hash* hash, void* key, void* value)
{
	int location, mutexIndex;
	node *runner, *currNode;

	//printf("value = %s\n", (char*)value);

	if (hash == NULL || key == NULL | value == NULL)
		return -1;  // error

	location = (hash->myHashFunc(key)) % hash->size;
	mutexIndex = location % MUTEX_FACTOR;
	pthread_mutex_lock(&hash->locks[mutexIndex]);

	//printf("location = %d", location);

	if (hash->arr[location] == NULL)
	{
		hash->arr[location] = malloc(sizeof(node));
		hash->arr[location]->key = key;
		hash->arr[location]->value = value;
		hash->arr[location]->next = NULL;
		pthread_mutex_unlock(&hash->locks[mutexIndex]);
		return 0;  // no dups
	}
	else
	{
		runner = hash->arr[location];
		do{
			currNode = runner;
			runner = runner->next;
		} while (runner != NULL);

		currNode->next = malloc(sizeof(node));
		currNode->next->key = key;
		currNode->next->value = value;
		currNode->next->next = NULL;
		pthread_mutex_unlock(&hash->locks[mutexIndex]);
		printf("return 1\n");
		return 1; // dup found
	}
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
