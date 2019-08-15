#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "timet.h"

int month_length[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

void addDate(cDate_t* date1, cDate_t* date2)
{	
	if (date1 == NULL || date2 == NULL)
		return;
	
	int month = date1->month > date2->month ? date1->month : date2->month;
	int year = date1->year > date2->year ? date1->year : date2->year;

	int dayRemainder;
	int yearReminder = 0, leap = 0;

	if (month == 2) 
	{
		leap = year % 4 == 0 ? 1 : 0;
		dayRemainder = (date1->day + date2->day) / (month_length[month - 1] + 1 + leap);
	}
	else
		dayRemainder = (date1->day + date2->day) / (month_length[month - 1] + 1);

	
	date1->day = (date1->day + date2->day) % (month_length[month - 1] + 1 + leap);
	date1->day += dayRemainder;

	date1->month = (month + dayRemainder) % 12;
	if (date1->month == 1)
	{
		yearReminder = 1;
	}
	date1->year = year + yearReminder;

}

int getDay(cDate_t* date)
{
	return date->day;
}

int getMonth(cDate_t* date)
{
	return date->month;
}

int getYear(cDate_t* date)
{
	return date->year;
}


void addTime(cTime_t* t1, cTime_t* t2)
{
	int sec, min;

	if (t1 == NULL || t2 == NULL)
		return;

	sec = (t1->seconds + t2->seconds) / 60;
	t1->seconds = (t1->seconds + t2->seconds) % 60;
	min = (t1->minutes + t2->minutes) / 60;
	t1->minutes = (t1->minutes + t2->minutes) % 60 + sec;
	t1->hours = (t1->hours + t2->hours + min) % 24;

}

void printTime(cTime_t* ctime_t, int format)
{
	char* ampm = malloc(sizeof(char) * 3);
	int hours = ctime_t->hours < 13 ? ctime_t->hours : ctime_t->hours - 12;
	
	if (format == 1)
	{
		printf("%d:%d:%d\n", ctime_t->hours, ctime_t->minutes, ctime_t->seconds);
	}
	else if (format == 2)
	{
		ampm = ctime_t->hours < 13 ? "AM" : "PM";
		printf("%d:%d:%d %s\n", hours, ctime_t->minutes, ctime_t->seconds, ampm);
	}
	else
		return;
}

void printDate(cDate_t* date, int format)
{
	//char* ampm = malloc(sizeof(char) * 3);
	//int hours = ctime_t->hours < 13 ? ctime_t->hours : ctime_t->hours - 12;

	if (format == 1)
	{
		printf("%d/%d/%d\n", date->day, date->month, date->year);
	}
	else if (format == 2)
	{
		printf("%d/%d/%d\n", date->month, date->day, date->year);
	}
	else
		return;
}

cTime_t* createTimeObject()
{
	cTime_t* object;

	object = malloc(sizeof(cTime_t));
	if (object == NULL)
		return NULL;

	return object;
}

cDate_t* createDateObject()
{
	cDate_t* object;

	object = malloc(sizeof(cDate_t));
	if (object == NULL)
		return NULL;

	return object;
}

int setTime(cTime_t* cTime, int sec, int min, int h)
{
	if (cTime == NULL || sec < 0 || sec > 59 || min < 0 || min > 59 || h < 0 || h > 23)
	{
		return 0;
	}
	else
	{
		cTime->seconds = sec;
		cTime->minutes = min;
		cTime->hours = h;

		return 1;
	}
}

int setDate(cDate_t* date, int day, int month, int year)
{
	if (date == NULL || day < 0 || day > 31 || month < 0 || month > 12 || year < 0)
	{
		return 0;
	}
	else
	{
		date->day = day;
		date->month = month;
		date->year = year;

		return 1;
	}

return 1;
}
