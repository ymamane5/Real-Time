#include<stdio.h>
#include<semaphore.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include "wQueue.h"

wQueue* createQueue(int size)
{
	wQueue* newQueue;
	newQueue = malloc(sizeof(wQueue));
	newQueue->arr = malloc(sizeof(void*) * size);
	newQueue->head = 0;
	newQueue->tail = 0;
	newQueue->count = 0;
	newQueue->size = size;
	sem_init(&(newQueue->semE), 0, 0);
	sem_init(&(newQueue->semF), 0, size);

	return newQueue;
}

void printQueue(wQueue* queue)
{
	int i, index = queue->head;

	printf("head = %d\ntail = %d \ncount = %d\n", queue->head, queue->tail, queue->count);
	//printf("arr[0] = %d\n", *(int*)(queue->arr[0]));
	printf("arr = ");
	for(i = 0; i < queue->count; i++)
	{
		printf("%d  ", *(int*)queue->arr[index++]);
		index = (index + 1) % queue->size;
	}
	if(queue->count == 0)
		printf("[Empty]\n");
	printf("\n");

}

void enqueue(wQueue* queue, void* item)
{
	printf("***inside enqueue***\n");
	printf("queue->arr[%d] = %s\n",queue->tail ,(char*)(queue->arr[queue->tail]));
	sem_wait(&queue->semF);
	pthread_mutex_lock(&(queue->lock));
	queue->arr[queue->tail] = item;
	//printf("insert to   : queue[%d] = %p\n", queue->tail, &queue->arr[queue->tail]);
	//printf("enqueue got: %s\n", (char*)queue->arr[queue->tail]);
	queue->tail = (queue->tail + 1) % (queue->size);
	queue->count++;	
	pthread_mutex_unlock(&(queue->lock));
	sem_post(&queue->semE);
}

void* dequeue(wQueue* queue)
{
	void* temp;
	int tempNum;
	printf("***inside dequeue***\n");
	printf("queue->arr[%d] = %s\n",queue->head ,(char*)(queue->arr[queue->head]));
	//printf("dequeue from: queue[%d] = %p\n", queue->head, queue->arr[queue->head]);
	sem_wait(&queue->semE);
	pthread_mutex_lock(&(queue->lock));
	temp = queue->arr[queue->head];
	//printf("dequeue send: %s\n", (char*)temp);
	queue->head = (queue->head + 1) % (queue->size);
	queue->count--;
	pthread_mutex_unlock(&(queue->lock));
	sem_post(&queue->semF);
	
	return temp;
}

void destroyWQueue(wQueue* queue)
{
	free(queue->arr);
	free(queue);
}

