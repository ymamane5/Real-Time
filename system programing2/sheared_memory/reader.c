#include <sys/ipc.h> 
#include <sys/shm.h> 
#include <stdio.h> 
#include <unistd.h>

int main() 
{ 
    int prev_num;

    // ftok to generate unique key 
    key_t key = ftok("shmfile",65); 
  
    // shmget returns an identifier in shmid 
    int shmid = shmget(key,4,0666|IPC_CREAT); 
  
    // shmat to attach to shared memory 
    int *num = (int*) shmat(shmid,(void*)0,0); 
    prev_num = *num;
    printf("Data read from memory: %d\n",*num);

    while(*num < 5)
    {
        if(*num != prev_num)
        {
            printf("Data read from memory: %d\n",*num);
            prev_num = *num;
        }
    } 
    //detach from shared memory  
    shmdt(num); 
    
    // destroy the shared memory 
    shmctl(shmid,IPC_RMID,NULL);

    return 0; 
} 