#ifndef DA_H
#define DA_H

typedef struct DA {
	int* arr;
	int capacity;
	int index;
}DA;

DA* create_DA(int capacity);
void printDA(DA* da);
int insert(DA* da, int num);
void destroy(DA* da);

#endif
