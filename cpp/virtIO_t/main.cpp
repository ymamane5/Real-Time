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

	//cout << "enter string" << endl;
	//cin >> str;

	asciiOut.open("test_file.txt", "r+");

	asciiOut >> num;
	cout << "found: " << num << endl;

	return 0;
}