#include <algorithm>
#include <set>
#include "meeting.h"

#ifndef DAY
#define DAY

using namespace std;

class classComp {
public:
	bool operator()(Meeting* first, Meeting* sec) const { 
		return first->getStartTime() < sec->getEndTime(); 
	}

private:
	int val;
};
class classEqual {
public:
	classEqual(float f) : val(f) {}
	bool operator()(Meeting* m2) const { 
		return (val == m2->getStartTime()); 
	}

private:
	float val;
};


class Day {

public:
	Day() {}
	~Day() {}

	void insertMeet(Meeting* m);
	float removeMeet(float begin);
	const Meeting& findMeeting(float begin);

	void printSet() const;

private:
	set<Meeting*, classComp> m_set;

};

void Day::insertMeet(Meeting* m)
{
	m_set.insert(m);
}

float Day::removeMeet(float begin)
{
	float m;

	auto it = find_if(m_set.begin(), m_set.end(), classEqual(begin));
	m = (*it)->getStartTime();

	if(it != m_set.end())
		m_set.erase(it);

	return m;
}

const Meeting& Day::findMeeting(float begin)
{
	auto it = find_if(m_set.begin(), m_set.end(), classEqual(begin));

	if(it == m_set.end())
		throw 1;

	return **it;
}

void Day::printSet() const
{
	for (auto it=m_set.cbegin(); it != m_set.cend(); ++it)
	{
    	(*it)->printMeeting();
    	//cout << "begin: " << (*it)->getStartTime();
    	//cout << "  end: " << (*it)->getEndTime();
    	//cout << "  room: " << (*it)->getRoom() << endl;
	}
}

#endif