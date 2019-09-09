#include<stdio.h>
#include<semaphore.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include "wQueue.h"

struct wQueue
{	
	void** arr;
	int head;
	int tail;
	int index;
	int size;
	pthread_mutex_t lock;
	sem_t semE;
	sem_t semF;
};

wQueue* createQueue(int size)
{
	wQueue* newQueue;
	newQueue = malloc(sizeof(wQueue));
	newQueue->arr = malloc(sizeof(void*) * size);
	newQueue->head = 0;
	newQueue->tail = 0;
	newQueue->index = 0;
	newQueue->size = size;
	sem_init(&(newQueue->semE), 0, size);
	sem_init(&(newQueue->semF), 0, size);

	return newQueue;
}

void printQueue(wQueue* queue)
{
	printf("head = %d\ntail = %d \ncount = %d\n", queue->head, queue->tail, queue->index);
	printf("arr[0] = %d\n", *(int*)(queue->arr[0]));
}

int enqueue(wQueue* queue, void* item)
{
	//void* temp = malloc(sizeof(void*));
	//temp = item;

	//sem_wait
	// mutex_lock
	if(queue->index < queue->size)
	{
		queue->arr[queue->tail] = item;
		queue->tail = (queue->tail + 1) % (queue->size);
		queue->index++;
		return 1;
	}
	//mutex_free
	//sem_post
	else
		return 0;

}

void* dequeue(wQueue* queue)
{
	void* temp;

	if(queue->index > 0)
	{
		temp = queue->arr[queue->head];
		queue->head = (queue->tail + 1) % (queue->size);
		queue->index--;
		return temp;
	}
}

