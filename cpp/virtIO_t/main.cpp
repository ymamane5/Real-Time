#include <string>
#include<iostream>
#include "virtIO.h"
#include "asciiIO.h"

using namespace std;

int main()
{
	asciiIO asciiOut;

	asciiOut.open("test_file.txt", "w");

	asciiOut << 5;

	return 0;
}