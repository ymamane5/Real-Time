#include<stdio.h>
#include<unistd.h>

int main()
{
	printf("in proc\n");
	sleep(3);
	int* p = 0;
	*p = 0;
}