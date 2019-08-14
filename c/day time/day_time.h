#ifndef DAYTIME
#define DAYTIME

typedef struct 
{
	int seconds;
	int minutes;
	int hours;
}cTime_t;

int setTime(cTime_t* cTime, int sec, int min, int h);
cTime_t* createTimeObject();
void printTime(cTime_t* ctime_t);
void addTime(cTime_t*, cTime_t*);

#endif