#include<stdio.h>
#include "virtIO.h"

#ifndef ASCII
#define ASCII

using namespace std;

class asciiIO : public virtIO {

public:
	asciiIO() {};
	~asciiIO() {};

	int open(string name, string mode);

	virtIO& operator>>(int& num); // read
	virtIO& operator<<(int num); // write

private:
	asciiIO(const asciiIO& a);
	asciiIO& operator=(const asciiIO& a);

};

#endif