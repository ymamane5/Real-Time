#include <stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include <sys/wait.h>

int main(int argc, char** argv)
{
	int pipefd[2];
	char* fd[2];
	char buff[20] = {0};
	
	pipe(pipefd);
	//printf("pipe: [%d, %d]\n", pipefd[0], pipefd[1]);
	write(pipefd[1], "hi", 2);

	if(fork() == 0)
	{
		read(pipefd[0], buff, 2);
		printf("child got: %s\n", buff);
		close(pipefd[0]);
		exit(0);
	}

	close(pipefd[1]);

	return 0;
}




	




