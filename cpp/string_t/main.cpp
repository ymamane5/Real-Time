#include<stdio.h>
#include<string.h>
#include<iostream>
#include "string_t.h"

using namespace std;

int main()
{
	char* temp1 = (char*)malloc(32);
	char* temp2 = (char*)malloc(32);
	int input, index;
	
	printf("Please enter string 1:\n");
	scanf("%s", temp1);

	string_t s1(temp1);
	string_t *s2 = new string_t();
	
	do 
	{
		printf("choose option:\n1. to upper case\n2. prepend\n3. operator +=\n4. operator <\n5. contains\n6. operator []\n");
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
			s2->setstring(temp2);
			s1.prepend(*s2);
			s1.print();
			break;
		case 3:
			printf("Enter string to concat\n");
			scanf("%s", temp2);
			s2->setstring(temp2);
			s1 += *s2;
			s1.print();
			break;
		case 4:
			printf("Enter second string to check\n");
			scanf("%s", temp2);
			s2->setstring(temp2);
			cout << "s1 < s2 ?  " << (s1 < *s2) << "\n";
			break;
		case 5:
			printf("Enter substring\n");
			scanf("%s", temp2);
			s2->setstring(temp2);
			cout << "s1.contains(s2) = " << s1.contains(*s2) << "\n";
			break;
		case 6:
			cout << "Enter index";
			cin >> index;
			cout << "s[index] = " << s1[index] << "\n";
			break;
		case 7:
			//cout << s1;
			break;
		default:
			break;
		}

	} while (input < 9);
	
	return 0;
}
