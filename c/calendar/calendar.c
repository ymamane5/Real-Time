#include<stdio.h>
#include "calendar.h"


Calendar_t* creatAD()
{
	Calendar_t* calendar = malloc(sizeof(Calendar_t));
	calendar->capacity = 3;
	calendar->index = 0;
	calendar->day = malloc(sizeof(Meeting_t) * 3);
	if (calendar == NULL)
		return NULL;

	return calendar;
}

void printDay(Calendar_t* cal)
{
	int i;

	for (i = 0; i < cal->index; i++)
	{
		printf("meeting from %f to %f in room %d", cal->day[i].begin, cal->day[i].end, cal->day[i].room_num);
	}
}

int insertMeeting(Calendar_t* cal, float begin, float end, int room)
{
	cal->day[cal->index].begin = begin;
	cal->day[cal->index].end = end;
	cal->day[cal->index].room_num = room;
	(cal->index)++;

	return 1;
}
