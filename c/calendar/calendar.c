#include<stdio.h>
#include<stdlib.h>
#include "calendar.h"


Calendar_t* creatAD(int size)
{
	Calendar_t* calendar = malloc(sizeof(Calendar_t));
	calendar->capacity = size;
	calendar->index = 0;
	calendar->day = malloc(sizeof(Meeting_t*) * size);
	if (calendar == NULL)
		return NULL;

	return calendar;
}

void printDay(Calendar_t* cal)
{
	int i;

	if(cal == NULL)
	{
		printf("calendar does not exist");
		return;
	}

	for (i = 0; i < cal->index; i++)
	{
		printf("meeting from %f to %f in room %d\n", cal->day[i]->begin, cal->day[i]->end, cal->day[i]->room_num);
	}
}

int insertMeeting(Calendar_t* cal, float begin, float end, int room)
{
	Meeting_t** temp;

	if(cal == NULL || begin < 0 || end < 0 || room < 0)
		return 0;

	if(cal->index >= cal->capacity)
	{
		temp = realloc(cal->day, (cal->index) * 2);
		if(temp != NULL)
		{
			cal->day = temp;
			(cal->capacity) *= 2;
		}
		else
			return 0;
	}

	cal->day[cal->index] = (Meeting_t*)malloc(sizeof(Meeting_t));
	cal->day[cal->index]->begin = begin;
	cal->day[cal->index]->end = end;
	cal->day[cal->index]->room_num = room;
	(cal->index)++;

	return 1;
}

int deleteMeeting(Calendar_t* cal, int begin)
{
	int i, j;

	if(cal->index == 0 || cal == NULL)
		return 0;

	for(i = 0; i < cal->index; i++)
	{
		if(cal->day[i]->begin == begin)
		{
			free(cal->day[i]);
			cal->index--;
			for( j = i; j < cal->index; j++)
			{
				cal->day[j] = cal->day[j + 1];
			}
		return 1;
		}
	}
	return 0;
}

Meeting_t* findMeeting(Calendar_t* cal, int begin)
{
	int i;

	for(i = 0; i < cal->index; i++)
	{
		if(cal->day[i]->begin == begin)
			return cal->day[i];
	}

	return NULL;
}

int detroyAD(Calendar_t* cal)
{
	int i;

	for(i = 0; i < cal->index; i++)
	{
		free(cal->day[i]);
		free(cal);
		cal = NULL;
	}
}
