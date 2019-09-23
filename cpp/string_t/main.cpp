#include<stdio.h>
#include<string.h>
#include<iostream>
#include "string_t.h"

using namespace std;

int main()
{
	char* temp1 = (char*)malloc(32);
	char* temp2 = (char*)malloc(32);
	int input;
	
	printf("Please enter string 1:\n");
	scanf("%s", temp1);

	string_t s1(temp1);
	string_t s2();
	
	do 
	{
		printf("choose option:\n1. to upper case");
		scanf("%d", &input);

		switch (input)
		{
		case 1:
			s1.mytoupper();
			s1.print();
			break;
		case 2:
			printf("Enter string to prepend\n");
			scanf("%s", temp2);
			s2.setstring(temp2);
			s1.prepend(s2);
			break;
		default:
			break;
		}

	} while (input < 9);
	{

	}

	

	
	
	s1.mytolower();
	s1.print();
	
	s1.print();
	//s1 += s2;
	//s1.print();
	//cout << (s1[4]) << "\n";
	//s1[4] = 'e';
	//cout << s1[4] << "\n";

	//cout << s1;
	

	return 0;
}