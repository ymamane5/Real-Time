#include <sys/ipc.h> 
#include <sys/shm.h> 
#include <stdio.h> 
#include <unistd.h>
  
int main() 
{ 
    int x;
    // ftok to generate unique key 
    key_t key = ftok("shmfile",65); 
  
    // shmget returns an identifier in shmid 
    int shmid = shmget(key,4,0666|IPC_CREAT); 
  
    // shmat to attach to shared memory 
    int *num = (int*) shmat(shmid,(void*)0,0); 
    *num = 0;
    printf("Write %d\n", *num);
    //scanf("%d", &x);  // wait for signal
    sleep(3);

    do {
       sleep(1);
       (*num)++;
       //*num = *num + 1;
       printf("Write %d\n", *num);
    } while(*num < 5);
      
    //detach from shared memory  
    shmdt(num); 
  
    return 0; 
} 