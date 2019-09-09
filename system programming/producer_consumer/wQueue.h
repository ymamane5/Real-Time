#ifndef WQUEUE
#define WQUEUE

typedef struct wQueue wQueue; 

wQueue* createQueue(int size);
void printQueue(wQueue* queue);
int enqueue(wQueue* queue, void* item);
void* dequeue(wQueue* queue);

#endif