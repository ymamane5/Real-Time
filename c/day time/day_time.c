#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include "day_time.h"

int month_length[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
char* month_name[12] = { "Jan", "Feb", "Mar", "Apr", "May", "June", "July", "Aug", "Sep", "Oct", "Nov", "Dec" };

void printAM(cTime_t* ctime_t);

cDate_t* createDateObject()
{
	cDate_t* dateObject;
	dateObject = malloc(sizeof(cDate_t));

	if (dateObject == NULL)
		return NULL;
	else
		return dateObject;
}

int setDate(cDate_t* date, int day, int month, int year)
{
	if (date == NULL || day < 1 || day > 31 || month < 1 || month > 12 || year < 0)
		return 0;

	date->day = day;
	date->month = month;
	date->year = year;

	return 1;
}

void addDate(cDate_t* date1, cDate_t* date2)
{
	int dayRemainder, month, year;
	int yearReminder = 0, leap = 0;

	if (date1 == NULL || date2 == NULL)
		return;

	month = date1->month > date2->month ? date1->month : date2->month;
	year = date1->year > date2->year ? date1->year : date2->year;

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

void printDate(cDate_t* date, int format)
{
	switch (format)
	{
	case 1:
		printf("%d/%d/%d\n", date->day, date->month, date->year);
		break;
	case 2:
		printf("%d %s %d", date->day, month_name[date->month - 1], date->year);
		break;
	default:
		break;
	}
}

cTime_t* createTimeObject()
{
	cTime_t* timeObject;
	timeObject = malloc(sizeof(cTime_t));

	if (timeObject != NULL)
		return timeObject;
	else
		return NULL;

}

int setTime(cTime_t* cTime, int h, int min, int sec)
{
	if (cTime == NULL || sec < 0 || sec > 59 || min < 0 || min > 59 || h < 0 || h > 23)
		return 0;
	
	cTime->hours = h;
	cTime->minutes = min;
	cTime->seconds = sec;
	return 1;
}

void addTime(cTime_t* t1, cTime_t* t2)
{
	int secR, minR;

	if (t1 == NULL || t2 == NULL)
		return;

	secR = (t1->seconds + t2->seconds) / 60;
	t1->seconds = (t1->seconds + t2->seconds) % 60;
	minR = (t1->minutes + t2->minutes + secR) / 60;
	t1->minutes = ((t1->minutes + t2->minutes) + secR) % 60;
	t1->hours = (t1->hours + t2->hours + minR) % 24;

}

void printTime(cTime_t* ctime_t, int format)
{
	switch (format)
	{
	case 1: 
		printf("%d:%d:%d\n", ctime_t->hours, ctime_t->minutes, ctime_t->seconds);
		break;
	case 2:
		printAM(ctime_t);
		break;
	default:
		break;
	}
}

void printAM(cTime_t* ctime_t)
{
	if(ctime_t->hours == 0)
		printf("%d:%d:%d AM\n", ctime_t->hours + 12, ctime_t->minutes, ctime_t->seconds);
	else if(ctime_t->hours > 0 && ctime_t->hours < 12)
		printf("%d:%d:%d AM\n", ctime_t->hours, ctime_t->minutes, ctime_t->seconds);
	else if(ctime_t->hours == 12)
		printf("%d:%d:%d PM\n", ctime_t->hours, ctime_t->minutes, ctime_t->seconds);
	else if(ctime_t->hours > 12 && ctime_t->hours < 24)
		printf("%d:%d:%d PM\n", ctime_t->hours - 12, ctime_t->minutes, ctime_t->seconds);
}
