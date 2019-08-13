#ifndef CAL
#define CAL

typedef struct MEETING {
	float begin;
	float end;
	int room_num;
}Meeting_t;

typedef struct CALENDAR {
	int capacity;
	int index;
	Meeting_t** day;
}Calendar_t;


Calendar_t* creatAD(int); 
void printDay(Calendar_t*);
int insertMeeting(Calendar_t* cal, float begin, float end, int room);
int deleteMeeting(Calendar_t* cal, int begin);
Meeting_t* findMeeting(Calendar_t* cal, int begin);
int detroyAD(Calendar_t* cal);

#endif
