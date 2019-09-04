#include<stdio.h>
#include<string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "hash.h"
#include "findDup.h"

#define HASH_SIZE 30

int isDir(char* name);

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

int scanTree(hash* myHash, char* name)
{
	struct stat sb;
	DIR* dir = opendir(name);
	struct dirent *entry;

	//printf("name = %s\n", name);

	if(!isDir(name)) // is File
	{
		printf("d_name = %s\n", entry->d_name);
		insert(myHash, entry->d_name, "test_value");
		return 1;
	}
	else //is Directory
	{
		while(entry = readdir(dir))
		{
			if(entry->d_type == 4 && (strcmp(entry->d_name, ".") != 0) && ((strcmp(entry->d_name, "..") != 0))) //is Directory
				scanTree(myHash, entry->d_name);
			else if((strcmp(entry->d_name, ".") != 0) && (strcmp(entry->d_name, "..") != 0))// is File
			{
				insert(myHash, entry->d_name, "test_value");
				//printf("d_name = %s\n", entry->d_name);
			}
		}
	}

/*    

     if (entry->d_type == DT_DIR)
     	printf("entry->d_type %d\n", entry->d_type);
     if (entry->d_type == DT_REG)
     	printf("regular file\n");

  */  

/*
    if (lstat(name, &sb) == -1) 
    {
          perror("lstat");
          return 0;
    }  
    if((sb.st_mode & S_IFMT) == S_IFDIR)
    	printf("directory\n");
    if((sb.st_mode & S_IFMT) == S_IFREG)
    	printf("regular file\n");
*/

	return 0;
}

int isDir(char* name)
{
	DIR* directory = opendir(name);

    if(directory != NULL)
    {
     closedir(directory);
     return 1;
    }
	else
		return 0;
}

int findDup(char* name)
{
	hash* myHash = createHash(HASH_SIZE, hashFunc, copareFunc);
	
	if (myHash == NULL)
	{
		printf("cannot create hash table\n");
		return 0;
	}

	scanTree(myHash, name);
/*
	insert(myHash, "key1", "value1");
	insert(myHash, "key2", "value2");
	insert(myHash, "key3", "value3");
	insert(myHash, "key4", "value4");
	insert(myHash, "key5", "value5");
	insert(myHash, "key6", "value6");
	insert(myHash, "key6", "valuedfgd6");
*/
	printHash(myHash);

	destroyHash(myHash);
}