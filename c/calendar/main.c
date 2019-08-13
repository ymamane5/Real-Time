#include<stdio.h>
#include<stdlib.h>
#include "calendar.h"

int main()
{
	float begin, end;
	int room, selection, exit = 0;
	Calendar_t* cal;
	Meeting_t* meeting_p;

	cal = creatAD(3);

	while(exit == 0)
	{

		printf("select operation:\n1. add meeting\n2. delete meeting\n3. find meeting\n4. delete calendar\n5. exit");
		scanf("%d",&selection);

		switch(selection)
		{
			case 1: {
				printf("insert begin time:\n");
				scanf("%f", &begin);
				printf("insert end time:\n");
				scanf("%f", &end);
				printf("insert room:\n");
				scanf("%d", &room);
				if (insertMeeting(cal, begin, end, room) == 1)
					printf("added sucssesfully\n");
				else
					printf("insertion failed");
			}
				break;
			case 2: {
				printf("insert begin time of meeting to delete:\n");
				scanf("%f", &begin);
				if(deleteMeeting(cal, begin) == 1)
					printf("meeting from %f deleted sucssesfully\n", begin);
				else
					printf("delete failed");
			}
				break;
			case 3: {
				printf("insert begin time of existing meeting:\n");
				scanf("%f", &begin);
				meeting_p = findMeeting(cal, begin);
				if(meeting_p != NULL)
					printf("meeting found:\nfrom %f to %f in room %d\n",meeting_p->begin, meeting_p->end, meeting_p->room_num);
				else
					printf("meeting does not exist");
			}
				break;
				case 4: {
					if(detroyAD(cal) == 1)
						printf("calendar delted sucssesfully");
					else
						printf("delete failed");
				}
			case 5: exit = 1;	

		}

		printDay(cal);
		printf("%d meetings\n", cal->index);
	}

	return 0;
}
