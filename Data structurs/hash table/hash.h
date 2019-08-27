#ifndef MYHASH
#define MYHASH
#include <stdlib.h>

typedef int(*hashFuction1)(unsigned char*);
typedef int(*compareFunction)(void*, void*); 

typedef struct node {
	void* key;
	void* value;
	struct node* next;
}node;

typedef struct hash {
	node** arr;
	int size;
	hashFuction1 myHashFunc;
	compareFunction compFunc;
}hash;

hash* createHash(int size, hashFuction1 hashFunc, compareFunction compFunc);
int insert(hash* hash, void* key, void* value);
void* hashfind(hash* hash, void* key);
int destroyHash(hash* hash);

#endif
