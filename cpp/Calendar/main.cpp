#include <string>
#include <set>
#include <vector>
#include <iostream>
#include "meeting.h"
#include "day.h"

using namespace std;



int main()
{
	int input;
	float begin, end;
	unsigned int room;
	Day d;

	Meeting m3(1,2,200);
	Meeting m2(3,4,400);
	Meeting m1(5,6,600);

	d.insertMeet(&m1);
	d.insertMeet(&m2);
	d.insertMeet(&m3);

	//d.printSet();
	//cout << endl;
	

	do {
		cout << "choose option:\n1. insert Meeting\n2. remove Meeting\n3. find meeting" << endl;
		cout << "4. print meetings\n5. exit" << endl;
		
		cin >> input;

		switch (input)
		{
		case 1:
			cout << "enter begin time:\n";
			cin >> begin;
			cout << "enter end time:\n";
			cin >> end;
			cout << "enter room number:\n";
			cin >> room;
			d.insertMeet(new Meeting(begin, end, room));
			break;
		case 2:
			cout << "enter begin time:\n";
			cin >> begin;
			cout << "meeting from " << d.removeMeet(begin) << " deleted succesfuly\n";
			break;
		case 3:
			cout << "enter begin time:\n";
			cin >> begin;
			cout << "meeting is: " << endl;
			d.findMeeting(begin).printMeeting();
			break;
		case 4:
			d.printSet();
			break;
		}

	} while (input < 5 && input > 0);

	return 0;
}