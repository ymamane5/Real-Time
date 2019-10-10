#include <algorithm>
#include <set>

#ifndef MEET
#define MEET

using namespace std;

class Meeting {

public:
	Meeting(float start, float end, unsigned int room);
	~Meeting() {}
	float getStartTime() const { return m_start; }
	float getEndTime() const { return m_end; }
	unsigned int getRoom() const { return m_room; }
	void printMeeting() const;


private:
	Meeting(const Meeting& m);
	Meeting& operator=(Meeting& m);

	float m_start;
	float m_end;
	unsigned int m_room;
};

Meeting::Meeting(float start, float end, unsigned int room)
{
	m_start = start;
	m_end = end;
	m_room = room;
}

void Meeting::printMeeting() const
{
	cout << "begin: " << m_start;
    cout << "  end: " << m_end;
    cout << "  room: " << m_room << endl;
}

#endif