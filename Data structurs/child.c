#include <stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>

int main(int argc, char const *argv[])
{
	if(argc > 1)
		printf("child got: %s\n", argv[1]);
	else
		printf("no message recieved\n\n");

	return 0;
}