#include<stdio.h>
#include<stdlib.h>
#include "calendar.h"

int main()
{
	float begin, end;
	int room;
	Calendar_t* cal;

	cal = creatAD(3);

	do{
		printf("insert begin time:\n");
		scanf("%f", &begin);
		printf("insert end time:\n");
		scanf("%f", &end);
		printf("insert room:\n");
		scanf("%d", &room);
		if (insertMeeting(cal, begin, end, room) == 1)
			printf("added sucssesfully\n");
	}
	while(begin == -1 || end == -1 || room == -1);

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
	free(cal->day);
	free(cal);

	
	return 0;
}
