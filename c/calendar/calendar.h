#ifndef CAL
#define CAL

typedef struct CALENDAR {
	int year;
	int month;
	DA day;
}Calendar_t;

typedef struct MEETING {
	float begin;
	float end;
	int room_num;
}Meeting_t;

typedef struct DA {
	Meeting_t* arr;
	int capacity;
	int index;
}DA;

Calendar_t* creatAD();  /* calendar */
DA* create_DA(int capacity);  /* dynamic array */
void printDay(DA* da);
void printMeeting(Meeting_t* m);
int insertMeeting(Calendar_t* cal, float begin, float end, int room);

#endif
