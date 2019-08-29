#include <stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include <sys/wait.h>

int main(int argc, char** argv)
{
	char* file = malloc(sizeof(char) * 20);
	int x, pipefd[2];

	if(argc < 2)
	{
		printf("please enter file to run\n");
		exit(0);
	}

	file[0] = '.';
	file[1] = '/';
	file[2] = 0;
	
	strcat(file, argv[1]);
	pipe(pipefd);
	printf("pipe: [%d, %d]\n", pipefd[0], pipefd[1]);

	//dup2(pipefd[1], 1);

	printf("sent to pipe\n");

	if(fork() == 0)
		if(execvp(file, argv) < 0)
			printf("cannot run file\n");
	
	wait(&x);

	return 0;
}




	




