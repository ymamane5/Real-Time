#include<stdio.h>
#include "virtIO.h"

#ifndef ASCII
#define ASCII

using namespace std;

class asciiIO : public virtIO {

public:
	asciiIO() {};
	~asciiIO() {};

	//int open(string name, string mode);
	asciiIO& operator>>(int& num); // read
	asciiIO& operator<<(int num); // write
	string getMode() const { return m_mode; } 

private:
	asciiIO(const asciiIO& a);
	asciiIO& operator=(const asciiIO& a);

};

#endif