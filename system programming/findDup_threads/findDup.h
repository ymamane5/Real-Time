#ifndef FDUP
#define FDUP

#define THREADS_COUNT 1

int findDup(char* name);
int scanTree(void* _queue, char* name);
void md5Print(unsigned char* str);

#endif