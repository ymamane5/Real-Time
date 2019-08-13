#include<stdio.h>
#include<stdlib.h>
#include "calendar.h"

int main()
{
	Calendar_t* cal;

	cal = creatAD();
	insertMeeting(cal, 4.5, 6.5, 205);

	printDay(&(cal->day));
	/*
	int i, capacity, num;
	DA* da_1;
	
	printf("please enter array size:\n");
	scanf_s("%d", &capacity);

	da_1 = create_DA(capacity);

	while (capacity <= 0)
	{
		printf("please enter positive number\n");
		scanf_s("%d", &capacity);
	}

	printf("capacity = %d\nindex = %d", da_1->capacity, da_1->index);

	printf("please enter numbers\n");
	do {
		scanf_s("%d", &num);
		insert(da_1, num);
	} while (num > 0);


	for (i = 0; i < da_1->index; i++)
		printf("%d ", da_1->arr[i]);
	

	getch();
	free(da_1->arr);
	destroy(da_1);
	*/
}



