#include <string>
#include<iostream>
#include "virtIO.h"
#include "asciiIO.h"

using namespace std;

int main()
{
	asciiIO asciiOut;
	string str;
	int num;
	double dnum;

	asciiOut.open("test_file.txt", "r+");

	asciiOut >> dnum; // read
	cout << "found: " << dnum << endl;
	asciiOut >> num; // read
	cout << "found: " << num << endl;

	asciiOut << 1234;



	getchar();

	return 0;
}