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

#endif
