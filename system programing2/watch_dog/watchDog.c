#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

int main()
{
	int status, exitFlag = 0;
	char arg[10] = "./proc";

	while(!exitFlag)
	{
		if(fork()) // parent
		{
			wait(&status);
			if(!WIFEXITED(status))
				printf("restarting..\n");
			else
				exitFlag = 1;
		}
		else // child
		{
			execlp("./proc", "./proc", NULL);
			perror("execv: ");
		}
	}
}