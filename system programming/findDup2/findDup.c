#include<stdio.h>
#include<string.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <openssl/md5.h>
#include <fcntl.h>
#include <unistd.h>
#include "hash.h"
#include "findDup.h"

#define HASH_SIZE 10000

int isDir(char* name);
unsigned char* md5(char* name);
void md5Print(unsigned char* str);

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
	int insert_res, dupflag = 0, fd;
	char pathName[100];

	if(!dir) // is File
	{
		stat(name, &sb);
		if(!S_ISREG(sb.st_mode)) // is not File or Directory
			return -1;	
	}
	else //is Directory
	{
		while(entry = readdir(dir))
		{
			if(entry->d_type == 4 && (strcmp(entry->d_name, ".") != 0) && ((strcmp(entry->d_name, "..") != 0))) //is Directory
				scanTree(myHash, entry->d_name);
			else if((strcmp(entry->d_name, ".") != 0) && (strcmp(entry->d_name, "..") != 0))// is File
			{
				strcpy(pathName, name);
				strcat(pathName, "/");
				strcat(pathName, entry->d_name);
				
				//printf("pathName = %s\n", pathName);	

				insert_res = insert(myHash, md5(pathName), entry->d_name);
				if(insert_res == 0)
					printf("Eror: cannot insert [%s, %s]\n", entry->d_name, "test_value");
				else if(insert_res == 2)
					dupflag = 1;
			}
		}
	}

	return dupflag;

	return 0;
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
	int scan_result;
	hash* myHash = createHash(HASH_SIZE, hashFunc, copareFunc);
	
	if (myHash == NULL)
	{
		printf("cannot create hash table\n");
		return 0;
	}

	scan_result = scanTree(myHash, name);

	if(scan_result == -1)
		printf("not valid file name\n");
	else if(scan_result == 0)
		printf("no duplications found!\n");
	else 
		printf("doplication found!\n");

	printf("files list:\n");
	printHash(myHash);

	destroyHash(myHash);
}

