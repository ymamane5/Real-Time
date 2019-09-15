#include<stdio.h>
#include<semaphore.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include "wQueue.h"

void printArray(wQueue* queue);

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

void printArray(wQueue* queue)
{
	int i;

	for(i = 0; i < queue->count; i++)
		printf("%s  ", (char*)queue->arr[i]);

	printf("\n");
}

void enqueue(wQueue* queue, void* item)
{
	sem_wait(&queue->semF);
	pthread_mutex_lock(&(queue->lock));
	queue->arr[queue->tail] = item;
	queue->tail = (queue->tail + 1) % (queue->size);
	queue->count = queue->count + 1;	
	pthread_mutex_unlock(&(queue->lock));
	sem_post(&queue->semE);
}

void* dequeue(wQueue* queue)
{
	void* temp;
	int tempNum;

	sem_wait(&queue->semE);
	pthread_mutex_lock(&(queue->lock));
	temp = queue->arr[queue->head];
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

