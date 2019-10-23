#include<iostream>
#include<stdio.h>
#include "virtIO.h"

#ifndef ASCII
#define ASCII

using namespace std;

class asciiIO : public virtIO {

public:
	asciiIO() {};
	~asciiIO() {};

	template<class T>
	asciiIO& operator>>(T& val); // read
	template<class T>
	asciiIO& operator<<(T num); // write
	string getMode() const { return m_mode; } 

private:
	asciiIO(const asciiIO& a);
	asciiIO& operator=(const asciiIO& a);

};

template<class T>
asciiIO& asciiIO::operator<<(T val) // write
{
	char format[5];

	if (m_mode != "w" && m_mode != "w+" && m_mode != "r+")
	{
		printf("no premossion to write\n");
		m_status = writeEror;
	}

	getFormat(val, format);
	fprintf(m_fp, format, val);
	//m_position = ftell(m_fp);
	return *this;

}

template<class T>
asciiIO& asciiIO::operator>>(T& val) // read
{
	char format[5];
	
	if (m_mode != "r" && m_mode != "r+")
	{
		m_status = bad_access;
		return *this;
	}
	if (getFormat(val, format) == -1)
	{
		cout << typeid(val).name() << endl;
		m_status = readEror;
	}

	fscanf(m_fp, format, &val);
	return *this;
}

#endif