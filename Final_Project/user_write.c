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

void* write_func(void* thread_num);

static int cycles = 1;
 
int main(int argc, char *argv[]) // argv[1] = thread count
{
   
    int thread_count, i, j;
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
        pthread_create(&read_thread[i], NULL, write_func, (void*)&thread_num[i]);
    }
    for(j = 0; j < thread_count; j++)
        pthread_join(read_thread[j], NULL);
    

    return 0;
}

void* write_func(void* thread_num)
{
        int fd;
        data_t* data_element = malloc(sizeof(data_t));
        char char_thread_num[16];

        snprintf(char_thread_num, 10, "%d", *(int*)thread_num);
        printf("Opening Driver\n");
        fd = open("/dev/mqueue0", O_RDWR);
        if(fd < 0) {
                printf("Cannot open device file...\n");
                return 0;
        }
        //printf("Writing Value to Driver\n");
        data_element->str = char_thread_num;
        data_element->size = strlen(char_thread_num);
        printf("writing %s\n", char_thread_num);
        ioctl(fd, QUEUE_WRITE, data_element); 

        printf("Closing Driver\n");
        close(fd);
}