#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include<sys/ioctl.h>
#include <pthread.h>
#include "mq.h"

void* read_func(void* thread_num);

static int cycles = 1;
 
int main(int argc, char *argv[]) // argv[1] = thread count
{
    int thread_count = 1, i, j;
    pthread_t* read_thread;
    int* thread_num;

    if(argc < 2)
    {
            printf("too few arguments\n");
            return 0;
    }
    thread_count = atoi(argv[1]);
    read_thread = malloc(sizeof(pthread_t) * thread_count);
    thread_num = malloc(sizeof(int) * thread_count);

    for(i = 0; i < thread_count; i++)
    {
        thread_num[i] = i;
        pthread_create(&read_thread[i], NULL, read_func, (void*)&thread_num[i]);
    }
    for(j = 0; j < thread_count; j++)
    {
        pthread_join(read_thread[j], NULL);
    }

    return 0;
}

void* read_func(void* thread_num)
{
    int fd, i;

    data_t* data_element = malloc(sizeof(data_t));
    data_element->str = malloc(sizeof(char) * 100);

    printf("Opening Driver\n");
    fd = open("/dev/mqueue0", O_RDWR);
    if(fd < 0) {
            printf("Cannot open device file...\n");
            return 0;
    }

    printf("Reading Values from Driver..\n");
    for(i = 0; i < cycles; i++)
    {
         ioctl(fd, QUEUE_READ, data_element->str);
         printf("thread[%d] read: %s\n", *((int*)thread_num), data_element->str);
    }

    printf("Closing Driver\n");
    close(fd);
}