#include<stdio.h>
#include<string.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include<pthread.h>
#include <openssl/md5.h>
#include <fcntl.h>
#include <unistd.h>
#include "hash.h"
#include "findDup.h"
#include "wQueue.h"

unsigned char* md5(char* name);
void md5Print(unsigned char* str);
void* hashInsertHandler(wQueue* queue);
char* addPreName(char* name);

hash* myHash;
char* termin = "terminate";
char globalName[50];
int counter = 0;

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

int scanTree(void* _queue, char* basePath)
{
	struct stat sb;
	DIR* dir = opendir(basePath);
	struct dirent *entry;
	int insert_res, dupflag = 0, fd;
	char currPath[100];
	wQueue* queue = (wQueue*)_queue;

	if(!dir) // is File
	{
		stat(basePath, &sb);
		if(!S_ISREG(sb.st_mode)) // is not File or Directory
			return -1;	
	}
	else //is Directory
	{
		while(entry = readdir(dir))
		{
			
			if(entry->d_type == 4 && (strcmp(entry->d_name, ".") != 0) && ((strcmp(entry->d_name, "..") != 0))) //is Directory
				{
				strcpy(currPath, basePath);
				strcat(currPath, "/");
				strcat(currPath, entry->d_name);
				scanTree(queue, currPath);
				}
			else if((strcmp(entry->d_name, ".") != 0) && (strcmp(entry->d_name, "..") != 0))// is File
			{
				char* path = malloc(sizeof(char) * 100);
				strcpy(currPath, basePath);
				strcat(currPath, "/");
				strcat(currPath, entry->d_name);
				strcpy(path, currPath);

				enqueue(queue, (void*)path);
				strcpy(currPath, basePath);
				
			}	
		}	

		return dupflag;
	}

}

void* hashInsertHandler(wQueue* queue)
{
	char *pathName, *temp;
	int res, *insert_res = calloc(sizeof(int), 1);

	while(1)
	{
		
		pathName = (char*)dequeue(queue);

		if(!strcmp(pathName, termin))
		{
			enqueue(queue, termin);
			pthread_exit((void*)insert_res);
		}

		res = insert(myHash, md5(pathName), pathName);
		if(res == -1)
			printf("Eror: cannot insert %s\n", pathName);

		*insert_res += res;
	}	
}

char* addPreName(char* name)
{
	char* pathName = malloc(sizeof(char) * 100);

	strcpy(pathName, globalName);
	strcat(pathName, "/");
	strcat(pathName, name);

	return pathName;
}

void md5Print(unsigned char* str)
{
	int n;

	for(n=0; n<MD5_DIGEST_LENGTH; n++)
        printf("%02x", str[n]);
}

unsigned char* md5(char* name)
{
    int n, fd;
    MD5_CTX c;
    char buf[512];
    ssize_t bytes;
    unsigned char *out = malloc(MD5_DIGEST_LENGTH);

    MD5_Init(&c);

    if((fd = open(name, O_RDONLY)) < 0)
    {
        printf("md5: cannot open file\n");
        return 0;
    }
   
    bytes=read(fd, buf, 512); 
    while(bytes > 0)
    {
        MD5_Update(&c, buf, bytes);
        bytes=read(fd, buf, 512);
    }

    MD5_Final(out, &c);

    return out;       
}

int findDup(char* name)
{
	int scan_result = 0, i;
	myHash = createHash(HASH_SIZE, hashFunc, copareFunc);
	wQueue* queue = createQueue(QUEUE_SIZE);
	pthread_t threads[THREADS_COUNT];
	void* hashHandler = hashInsertHandler, *ret;
	char* path_buff = malloc(sizeof(char) * 100);

	strcpy(globalName, name);
	strcpy(path_buff, name);
	
	if (myHash == NULL)
	{
		printf("cannot create hash table\n");
		return 0;
	}

	for(i = 0; i < THREADS_COUNT; i++)
	{
		pthread_create(&threads[i], NULL, hashHandler, (void*)queue);
	}
	
	if(scanTree(queue, path_buff) == -1)
	{
		printf("not valid file name\n");
		return -1;
	}

	enqueue(queue, termin);

	for(i = 0; i < THREADS_COUNT; i++)
	{
		pthread_join(threads[i], &ret);
		scan_result += *(int*)ret;
	}

	if(scan_result == -1)
		printf("not valid file name\n");
	else if(scan_result == 0)
		printf("no duplications found!\n");
	else 
		printf("doplication found!\n");

	printf("files list:\n");
	printHash(myHash);
	destroyHash(myHash);

	return 1;
}
