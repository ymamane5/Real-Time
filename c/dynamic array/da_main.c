#include<stdio.h>
#include<stdlib.h>
#include "da.h"

int main()
{
	int i, capacity, num;
	DA* da_1;
	
	printf("please enter array size:\n");
	scanf("%d", &capacity);

	while (capacity <= 0)
	{
		printf("please enter positive number\n");
		scanf("%d", &capacity);
	}

	da_1 = create_DA(capacity);
	if(da_1 == NULL)
	{
		printf("faild to allocate memory, exiting..\n");
		exit(0);
	}

	printf("please enter numbers\n");
	do {
		scanf("%d", &num);
		insert(da_1, num);
	} while (num > 0);

	printDA(da_1);
	destroy(da_1);
}
