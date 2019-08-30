#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "day_time.h"

int main()
{
	/*------------------------ time-----------------------------*/
	cTime_t *cTime1, *cTime2;
	cTime1 = createTimeObject();
	cTime2 = createTimeObject();

	if (setTime(cTime1, 11, 5, 13) == 1)
		printTime(cTime1, 1);

	printf("+\n");
	if (setTime(cTime2, 7, 9, 50) == 1)
		printTime(cTime2, 1);

	printf("=\n");
	addTime(cTime1, cTime2);
	printTime(cTime1, 1);
	printTime(cTime1, 2);
	printf("\n\n");


	free(cTime1);
	free(cTime2);

	/*------------------------------date-------------------------------*/
	cDate_t *date1, *date2;
	date1 = createDateObject();
	date2 = createDateObject();

	if(setDate(date1, 25, 8, 2009) == 1)
		printDate(date1, 1);
	printf("+\n");
	if(setDate(date2, 8, 8, 2009))
		printDate(date2, 1);
	
	addDate(date1, date2);
	printf("=\n");
	printDate(date1, 1);
	printDate(date1, 2);

	free(date1);
	free(date2);
	
	return 0;
}
