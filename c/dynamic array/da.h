#ifndef DA_H
#define DA_H

struct DA {
	int* arr;
	int capacity;
	int index;
};

void create_DA(int);
void printDA(DA* da);
int insert(DA* da, int num);
void destroy(DA* da);

#endif
