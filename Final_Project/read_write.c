#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <pthread.h>
#include <errno.h>
#include "mq.h"

void* write_func(void* thread_num);
void* read_func(void* thread_num);

int msg_sent = 0, msg_recieved = 0;
pthread_mutex_t r_lock;
pthread_mutex_t w_lock;

static int cycles;
 
int main(int argc, char *argv[]) // argv[1] = thread count, argv[2] = cycles
{
   
    int thread_count, i, j;
    pthread_t* read_thread;
    pthread_t* write_thread;
    int* thread_num_read;
    int* thread_num_write;

     if(argc < 3)
    {
        printf("too few arguments\n");
        return 0;
    }
    thread_count = atoi(argv[1]);
    read_thread = malloc(sizeof(pthread_t) * thread_count);
    write_thread = malloc(sizeof(pthread_t) * thread_count);
    thread_num_read = malloc(sizeof(int) * thread_count);
    thread_num_write = malloc(sizeof(int) * thread_count);
    cycles = atoi(argv[2]);
    pthread_mutex_init(&r_lock, NULL);
    pthread_mutex_init(&w_lock, NULL);

    for(i = 0; i < thread_count; i++)
    {
        thread_num_read[i] = i;
        pthread_create(&read_thread[i], NULL, read_func, (void*)&thread_num_read[i]);
        thread_num_write[i] = i;
        pthread_create(&write_thread[i], NULL, write_func, (void*)&thread_num_write[i]);
    }
    for(j = 0; j < thread_count; j++)
    {
        pthread_join(read_thread[j], NULL);

    }
    free(read_thread);
    free(thread_num_read);
    free(thread_num_write);

    printf("sent = %d\nrecieved = %d\n", msg_sent, msg_recieved);

    return 0;
}

void* write_func(void* thread_num)
{
        int fd, i;
        data_t* data_element = malloc(sizeof(data_t));
        char char_thread_num[16];

        snprintf(char_thread_num, 10, "%d", *(int*)thread_num);
        fd = open("/dev/mqueue0", O_RDWR);
        if(fd < 0) {
                printf("Cannot open device file...\n");
                return 0;
        }
        data_element->str = char_thread_num;
        data_element->size = strlen(char_thread_num);
        for(i = 0; i < cycles; i++)
        {
            if(ioctl(fd, QUEUE_WRITE, data_element) == -1)
            {
                perror("ioctl");
                return 0;
            }
            pthread_mutex_lock(&w_lock);
            msg_sent++;
            pthread_mutex_unlock(&w_lock);
        }

        close(fd);
}

void* read_func(void* thread_num)
{
    int fd, i;

    data_t* data_element;

    fd = open("/dev/mqueue0", O_RDWR);
    if(fd < 0) {
            printf("Cannot open device file...\n");
            return 0;
    }
    for(i = 0; i < cycles; i++)
    {
        data_element = malloc(sizeof(data_t));
        data_element->str = malloc(sizeof(char) * 10);
        if(ioctl(fd, QUEUE_READ, data_element->str) == -1)
        {
            perror("ioctl");
            return 0;
        }
        pthread_mutex_lock(&r_lock);
        msg_recieved++;
        pthread_mutex_unlock(&r_lock);
    }

    close(fd);
}