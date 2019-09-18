#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
​
void function(int number, siginfo_t* info, void* three)
{
	char* msg="HEY\n";
	write(1,msg,strlen(msg));
}
​
int main()
{
	struct sigaction act;
​
	memset(&act,0,sizeof(struct sigaction));
	act.sa_sigaction=function;
	act.sa_flags=SA_SIGINFO;
	sigaction(SIGINT,&act,NULL);
​
	sleep(5);
​
	return 0;
}