/* Passing data between two threads using Queue (GAsyncQueue) */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <glib.h>

void* reader();

const size_t buff_size = 55;
const size_t loops = 10000;
GAsyncQueue* my_queue;

int main(int argc, char const *argv[])
{
	int i, fd;
	char* buff;
	pthread_t thread1_id;
	pthread_t thread2_id;
	int* id1 = malloc(sizeof(int));
	int* id2 = malloc(sizeof(int));

	my_queue = g_async_queue_new();
	*id1 = 1;
	*id2 = 2;

	fd = open("/dev/urandom", O_RDONLY);
	if(fd < 0) {
            printf("Cannot open device file...\n");
            return 0;
    }
    printf("sending %ld messages\n", loops);
    pthread_create(&thread1_id, NULL, reader, (void*)id1);
    pthread_create(&thread2_id, NULL, reader, (void*)id2);

    //printf("writing data to queue..\n");
    for(i = 0; i < loops; i++)
    {
    	buff = malloc(buff_size);
    	if(read(fd, buff, buff_size) == 0)
    	{
    		perror("read");
    		break;
    	}
    	g_async_queue_push(my_queue, (void*)buff);
    }
    //sleep(1);
    buff = malloc(buff_size);
    strcpy(buff, "END");
    g_async_queue_push(my_queue, (void*)buff);

    pthread_join(thread1_id, NULL);
    pthread_join(thread2_id, NULL);
    close(fd);

	return 0;
}

void* reader(void* id)
{
	gpointer data;
	int counter = 0;

	data = g_async_queue_pop(my_queue);
	if(strcmp((char*)data, "END") == 0)
	{
		g_async_queue_push(my_queue, data);
		printf("thread %d read %d\n", *(int*)id, counter);
		return 0;
	}
	counter++;
	do {
    	//printf("%s\n", (char*)data);
    	data = g_async_queue_pop(my_queue);
    	if(strcmp((char*)data, "END") == 0)
		{
			g_async_queue_push(my_queue, data);
			printf("thread %d read %d\n", *(int*)id, counter);
			return 0;
		}
    	counter++;
    } while(1);

    printf("thread %d read %d\n", *(int*)id, counter);
    return 0;
}
