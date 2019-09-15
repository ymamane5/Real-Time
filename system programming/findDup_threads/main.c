#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include <sys/wait.h>
#include "hash.h"
#include "findDup.h"

int main(int argc, char *argv[])
{	
	if(argc < 2)
	{
		printf("no directory name entered\n");
		return 0;
	}

	findDup(argv[1]);
	
	return 0;
}
