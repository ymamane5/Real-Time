#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<conio.h>
#include "timet.h"

int main()
{
	cTime_t *cTime1, *cTime2;
	cDate_t *cDate1, *cDate2;
	
	//time_date = time(0);
	
	cTime1 = createTimeObject();
	cTime2 = createTimeObject();
	cDate1 = createDateObject();
	cDate2 = createDateObject();

	setDate(cDate1, 31, 12, 2005);
	setDate(cDate2, 1, 12, 2005);

	printDate(cDate1, 1);
	printDate(cDate2, 1);
	addDate(cDate1, cDate2);
	
	printDate(cDate1, 1);

	free(cTime1);
	free(cTime2);
	free(cDate1);
	free(cDate2);

	return 0;
}
