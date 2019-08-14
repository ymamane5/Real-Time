#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "day_time.h"

int main()
{
	cTime_t *cTime1, *cTime2;

	cTime1 = createTimeObject();
	cTime2 = createTimeObject();

	if(setTime(cTime1, 20,23,13) == 1)
		printTime(cTime1);
	if(setTime(cTime2, 10,23,13) == 1)
		printTime(cTime1);
	
	addTime(cTime1, cTime2);
	printTime(cTime1);

	free(cTime1);
	free(cTime2);

	return 0;
}