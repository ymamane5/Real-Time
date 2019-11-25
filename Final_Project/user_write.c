#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include<sys/ioctl.h>
#include "mq.h"
 
//#define WR_VALUE _IOW('a','a',int32_t*)
//#define RD_VALUE _IOR('a','b',int32_t*)
 
int main(int argc, char *argv[])
{
        int fd;
        data_t* data_element = malloc(sizeof(data_t));
        int32_t value, number;
      
        if(argc < 2)
        {
                printf("no message detected\n");
                return 0;
        }
 
        printf("\nOpening Driver\n");
        fd = open("/dev/mqueue0", O_RDWR);
        if(fd < 0) {
                printf("Cannot open device file...\n");
                return 0;
        }
 
        printf("Writing Value to Driver\n");
        printf("msg length = %ld\n", strlen(argv[1]));
        data_element->str = argv[1];
        data_element->size = strlen(argv[1]);
        ioctl(fd, QUEUE_WRITE, data_element); 

        printf("Closing Driver\n");
        close(fd);
}