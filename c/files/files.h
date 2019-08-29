#ifndef FILES
#define FILES

#define MAX 60 
#define MAX_WORD 20

typedef struct
{
	char* str;
	int count;
}word_t;

typedef struct DA
{
	word_t** arr;
	int capacity;
	int index;
}DA;

void lastNLines(FILE* fp, int n);
void removeSpaces(FILE* fp);
void countletters(FILE* fp);
void countWords(FILE* fp);

DA* createDA(int capacity);
void insert(DA* da, char* buff);
void printDA(DA* da);
void destroyDA(DA* da);

#endif