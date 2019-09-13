#ifndef WQUEUE
#define WQUEUE
#include <semaphore.h>

#define THREAD_COUNT 1
#define QUEUE_SIZE 5

typedef struct wQueue
{	
	void** arr;
	int head;
	int tail;
	int count;
	int size;
	pthread_mutex_t lock;
	sem_t semE;
	sem_t semF;
}wQueue;

typedef struct producerStruct
{
	pthread_t producers[THREAD_COUNT];
	wQueue* queue;
	wQueue* ACKQueue;
	pthread_mutex_t lock;
}producerStruct;

typedef struct consumerStruct
{
	pthread_t consumers[THREAD_COUNT];
	wQueue* queue;
	wQueue* ACKQueue;
}consumerStruct;

wQueue* createQueue(int size);
void printQueue(wQueue* queue);
void enqueue(wQueue* queue, void* item);
void* dequeue(wQueue* queue);
void destroyWQueue(wQueue* queue);

producerStruct* createProducers(void* _queue, void* _ACKQueue);
consumerStruct* createConcumers(void* _queue, void* ACKQueue);
void createProducerThreads(producerStruct* prodS);
void createConcumerThreads(consumerStruct* prodS);
void joinProducers(producerStruct* prodS);
void joinConsumers(consumerStruct* consS);
void* producer(void* prodS);
void* consumer(void* prodS);

#endif