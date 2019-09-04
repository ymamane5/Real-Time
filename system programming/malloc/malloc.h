#ifndef MEM
#define MEM

#define SET_FREE(header) (*(unsigned int*) (header-4) & 0x7fffffff)
#define SET_OCCUPIED(header) (*(unsigned int*)(header-4) | 0x80000000)
#define HEADER_VALUE(header) (*(unsigned int*)(header-4) & 0x7fffffff) 
#define IS_OCCUPIED(header) ( (*(unsigned int*)(header-4) & 0x80000000) == 0 ? 0 : 1)

void* memInit(void* buffer, unsigned int size);
void* memAlloc(void* buffer, unsigned int size);
void* memFree(void* buffer, void* address);

#endif
