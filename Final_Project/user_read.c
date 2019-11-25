#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include<sys/ioctl.h>
#include "mq.h"
 
int main(int argc, char *argv[])
{
        int fd;
        data_t* data_element = malloc(sizeof(data_t));
        data_element->str = malloc(sizeof(char) * 100);
 
        printf("\nOpening Driver\n");
        fd = open("/dev/mqueue0", O_RDWR);
        if(fd < 0) {
                printf("Cannot open device file...\n");
                return 0;
        }

        printf("Reading Value from Driver\n");
        ioctl(fd, QUEUE_READ, data_element->str); 
        printf("Value is %s\n", data_element->str);
 
        printf("Closing Driver\n");
        close(fd);
}