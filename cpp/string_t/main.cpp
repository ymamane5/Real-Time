#include<stdio.h>
#include<string.h>
#include<iostream>
#include "string_t.h"

//using namespace std;

int main()
{
	

	char* temp1 = (char*)malloc(32);
	char* temp2 = (char*)malloc(32);
	strcpy(temp1, "abcd");
	strcpy(temp2, "efgh");

	string_t s1(temp1);
	string_t s2(temp2);  

	
	s1.mytoupper();
	s1.print();
	s1.mytolower();
	s1.print();
	s1.prepend(s2);
	s1.print();
	//s1 += s2;
	//s1.print();
	//cout << (s1[4]) << "\n";
	//s1[4] = 'e';
	//cout << s1[4] << "\n";

	//cout << s1;

	return 0;
}