#ifndef DAYTIME
#define DAYTIME

typedef struct
{
	int seconds;
	int minutes;
	int hours;
}cTime_t;

typedef struct
{
	int day;
	int month;
	int year;
}cDate_t;


int setTime(cTime_t* cTime, int sec, int min, int h);
cTime_t* createTimeObject();
void printTime(cTime_t* ctime_t, int format);
void addTime(cTime_t*, cTime_t*);
int getDay(cDate_t* date);
int getMonth(cDate_t* date);
int getYear(cDate_t* date);
cDate_t* createDateObject();
int setDate(cDate_t* date, int day, int month, int year);
void printDate(cDate_t* date, int format);
void addDate(cDate_t*, cDate_t*);


#endif
