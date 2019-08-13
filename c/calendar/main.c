#include<stdio.h>
#include<stdlib.h>
#include "calendar.h"

int main()
{
	Calendar_t* cal;

	cal = creatAD();
	if (insertMeeting(cal, 4.5, 6.5, 205) == 1)
		printf("added sucssesfully");

	printDay(cal);
	/*
	int i, capacity, num;
	DA* da_1;

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
	return 0;
}



