#include<stdio.h>
#include "calendar.h"


Calendar_t* creatAD()
{
	Calendar_t* calendar;
	calendar = malloc(sizeof(Calendar_t));
	calendar->year = 0;
	calendar->month = 1;
	calendar->day = *(create_DA(3));
	if (calendar == NULL)
		return NULL;

	return calendar;
}

DA* create_DA(int capacity)
{
	DA *da = malloc(sizeof(DA));
	da->capacity = capacity;
	da->index = 0;
	da->arr = (Meeting_t*)malloc(sizeof(Meeting_t) * capacity);

	return da;
}

void printDay(DA* da)
{
	int i;

	for (i = 0; i < da->index; i++)
	{
		printMeeting(&(da->arr[i]));
	}
}

void printMeeting(Meeting_t* m)
{
	printf("meeting from %f to %f in room %d", m->begin, m->end, m->room_num);
}

int insertMeeting(Calendar_t* cal, float begin, float end, int room)
{
	cal->day.arr[cal->day.index].begin = begin;
	cal->day.arr[cal->day.index].end = end;
	cal->day.arr[cal->day.index].room_num = room;
	(cal->day.index)++;

	return 1;
}