#include<stdio.h>
#include<string.h>
#include<iostream>
#include "string_t.h"

using namespace std;

int main()
{
	char* temp1 = (char*)malloc(32);
	char* temp2 = (char*)malloc(32);
	int input, index, length;
	bool caseSens;
	char ch;
	
	cout << "Please enter string 1:\n";
	cin >> temp1;

	string_t s1(temp1);
	string_t *s2 = new string_t();
	
	do 
	{
		cout <<"choose option:\n1. to upper case\n2. prepend\n3. operator +=\n4. operator <\n5. contains\n";
		cout << "6. operator []\n7. cout <<\n8. set case sensitive\n9. set capacity\n10. getFirstAccurance\n";
		cout << "11. getLastAccurance\n12. operator()\n13. exit\n";
		cin >> input;

		switch (input)
		{
		case 1:
			s1.mytoupper();
			s1.print();
			break;
		case 2:
			cout << "Enter string to prepend\n";
			cin >> temp2;
			s2->setstring(temp2);
			s1.prepend(*s2);
			s1.print();
			break;
		case 3:
			cout << "Enter string to concat\n";
			cin >> temp2;
			s2->setstring(temp2);
			s1 += *s2;
			s1.print();
			break;
		case 4:
			cout << "Enter second string to check\n";
			cin >> temp2;
			s2->setstring(temp2);
			cout << (s1 < *s2) << "\n";
			break;
		case 5:
			cout << "Enter substring\n";
			cin >> temp2;
			s2->setstring(temp2);
			cout << "s1.contains(s2) = " << s1.contains(*s2) << "\n";
			break;
		case 6:
			cout << "Enter index\n";
			cin >> index;
			cout << "s[index] = " << s1[index] << "\n";
			break;
		case 7:
			cin >> s1;
			cout << "string = " << s1 << "\n";
			/*
			cout << s1;
			cout << nextPowerOf2(11) << "\n";
			*/
			break;
		case 8:
			cout << "enter 1 for case sensitive or 0 else\n";
			cin >> index;
			cout << "previus caseSens = " << string_t::setCaseSens(index) << "\n";
			cout << "caseSens = " << string_t::getCaseSens() << "\n";
			break;
		case 9:
			cout << "enter capacity\n";
			cin >> index;
			cout << "previus capacity = " << s1.setCapacity(index) << "\n";
			cout << "current capacity = " << s1.getCapacity() << "\n";
			break;
		case 10:
			cout << "enter char\n";
			cin >> ch;
			cout << "index is: " << s1.getFirstAccurance(ch) << "\n";
			break;
		case 11:
			cout << "enter char\n";
			cin >> ch;
			cout << "index is: " << s1.getLastAccurance(ch) << "\n";
			break;
		case 12:
			cout << "enter start index\n";
			cin >> index;
			cout << "enter length\n";
			cin >> length;
			cout << "new string = " << s1(index,length) << "\n";
			break;
		default:
			break;
		}

	} while (input < 13 && input > 0);
	
	return 0;
}