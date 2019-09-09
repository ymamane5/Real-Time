#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>
#include "wQueue.h"

int main()
{
	wQueue* myQueue = createQueue(5);
	int i, x[6] = {3,4,5,6,7,8};
	void* temp;

	for(i = 0; i < 6; i++)
	{
		if(enqueue(myQueue, (void*)&x) == 0)
			printf("enqueue failed\n");
		else
			printf("enqueue succeeded\n");
	}

	temp = dequeue(myQueue);
	printf("dequeued: %d\n", *(int*)temp);

	printQueue(myQueue);

	return 0;
}