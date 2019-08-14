#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "day_time.h"

void addTime(cTime_t* t1, cTime_t* t2)
{
	int sec, min;

	if(t1 == NULL || t2 == NULL)
		return;

	sec = (t1->seconds + t2->seconds) / 60;
	t1->seconds = (t1->seconds + t2->seconds) % 60;
	min = (t1->minutes + t2->minutes) / 60;
	t1->minutes = (t1->minutes + t2->minutes) % 60 + sec; 
	t1->hours = (t1->hours + t2->hours + min) % 24;

}

void printTime(cTime_t* ctime_t)
{
	printf("%d:%d:%d\n", ctime_t->hours, ctime_t->minutes, ctime_t->hours);
}

cTime_t* createTimeObject()
{
	cTime_t* object;

	object = malloc(sizeof(cTime_t));
	if(object == NULL)
		return NULL;

	return object;
	
}

int setTime(cTime_t* cTime, int sec, int min, int h)
{
	if(cTime == NULL || sec < 0 || sec > 59 || min < 0 || min > 59 || h < 0 || h > 23)
	{
		return 0;
	}
	else 
	{
		cTime->seconds = sec;
		cTime->minutes = min;
		cTime->hours = h;
	}

	return 1;
}