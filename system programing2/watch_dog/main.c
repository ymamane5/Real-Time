#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

int main()
{
	int status;
	char arg[10] = "./proc";

	if(fork()) // parent
	{
		wait(&status);

	}
	else // child
	{
		execlp("proc", "./proc", NULL);
	}
}