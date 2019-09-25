#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <ctype.h>
#include<iostream>
#include "string_t.h"

using namespace std;
bool string_t::caseSens = false;
size_t string_t::default_capacity = 16;

string_t::string_t()
{
	mystr = new char;
	capacity = string_t::default_capacity;
}

string_t::string_t(const char* str)  // copy ctor
{
	capacity = nextPowerOf2(strlen(str) + 1);
	mystr = new char[capacity];
	strcpy(mystr, str);
}
string_t::string_t(const string_t &str)  // copy ctor
{
	capacity = nextPowerOf2(strlen(str.mystr) + 1);
	mystr = new char[capacity];
	strcpy(mystr, str.mystr);
}

string_t::~string_t()  // dstor
{
	delete[] mystr;
}

string_t& string_t::operator=(const string_t& str)  // str1 = str2
{
	if(this != &str)
	{
		setstring(str.getstring());
	}

	return *this;
}

int string_t::length() const
{
	return strlen(mystr);
}

void string_t::setstring(const char* str)
{
	if(strlen(str) < capacity)
	{
		strcpy(mystr, str);
	}
	else
	{
		capacity = nextPowerOf2(strlen(str) + 1);
		delete[] mystr;
		mystr = new char[capacity];
		strcpy(mystr, str);
	}
}

char* string_t::getstring() const
{
	return mystr;
}

int string_t::compare(const string_t& str) const
{
	if(caseSens == true)
		return strcmp(mystr, str.mystr);
	else
		return strcasecmp(mystr, str.mystr);
}

void string_t::print() const
{	
	printf("%s\n", mystr);
}

void string_t::mytoupper()
{
	for(int i = 0; i < strlen(mystr); i++)
	{
		mystr[i] = toupper(mystr[i]);
	}
}

void string_t::mytolower()
{
	for(int i = 0; i < strlen(mystr); i++)
	{
		mystr[i] = tolower(mystr[i]);
	}
}

void string_t::prepend(const char* str)
{
	char* temp = new char[strlen(str) + strlen(mystr) + 1];

	strcpy(temp, str);
	strcat(temp, mystr);
	setstring(temp);

	delete temp;
}

void string_t::prepend(string_t& str)
{
	prepend((const char*)str.mystr);
}

string_t& string_t::operator+=(const string_t& str)
{
	char* temp = new char[strlen(str.mystr) + strlen(mystr) + 1];

	strcpy(temp, mystr);
	strcat(temp, str.mystr);
	setstring(temp);

	return *this;
}

bool string_t::operator<(const string_t& str) const
{
	if(this->compare(str) < 0)
		return true;
	else
		return false;
}
bool string_t::operator>(const string_t& str) const
{
	if(this->compare(str) > 0)
		return true;
	else
		return false;
}

bool string_t::operator>=(const string_t& str) const
{
	if(this->compare(str) >= 0)
		return true;
	else
		return false;
}
bool string_t::operator<=(const string_t& str) const
{
	if(this->compare(str) <= 0)
		return true;
	else
		return false;
}
bool string_t::operator==(const string_t& str) const
{
	if(this->compare(str) == 0)
		return true;
	else
		return false;
}
bool string_t::operator!=(const string_t& str) const
{
	if(this->compare(str) != 0)
		return true;
	else
		return false;
}

string_t& string_t::operator()(int start, uint len)
{
	int i = 0;
	char* buff = new char[len + 1];

	while(i < len && mystr[start + i] != '\0')
	{
		buff[i] = mystr[start + i];
		i++;
	}

	buff[i] = '\0';
	setstring(buff);
	delete buff;

	return *this;
}

bool string_t::contains(const string_t& str) const
{
	if(caseSens == true)
	{
		if(strstr(this->mystr, str.mystr) != NULL)
			return true;
		else
			return false;
	}
	else
	{
		if(strcasestr(this->mystr, str.mystr) != NULL)
			return true;
		else
			return false;
	}
}
char string_t::operator[](int i) const
{
	if(i < strlen(mystr) && i >= 0)
		return mystr[i];
	else
	{
		std::cout << "Eror: operand outbound\n";
		return '\0';	
	}
}

char& string_t::operator[](int i)
{
	if(i < strlen(mystr) && i >= 0)
		return mystr[i];
	else
	{
		std::cout << "Eror: operand outbound\n";
		exit(0);	
	}
}

ostream& operator<<(ostream& os, string_t& str)
{
	os << str.getstring() << "\n";
	return os;
}

istream& operator>>(istream& is, string_t& str)
{
	char temp[32];
	is >> temp;

	str.setstring(temp); 
}

bool string_t::setCaseSens(bool flag)
{
	bool temp = caseSens;
	caseSens = flag;

	return temp;
}

size_t string_t::setCapacity(size_t size)
{
	size_t temp = capacity;

	if(size <= strlen(mystr))
	{
		cout << "cannot change capacity - too small for current object\n";
		return capacity;
	}
	else
	{
		capacity = size;
		return temp;
	}
}

size_t string_t::getFirstAccurance(char ch) const
{
	char *temp = new char[strlen(mystr)];

	if(caseSens == true)
		return (size_t)(strchr(mystr, ch) - mystr);
	else
	{
		strcpy(temp, mystr);
		for(int i = 0; i < strlen(temp); i++)
			temp[i] = tolower(temp[i]);

		tolower(ch);
		return (size_t)(strchr(temp, ch) - temp);
	}

	delete temp;
}

size_t string_t::getLastAccurance(char ch) const
{
	return (size_t)(strrchr(mystr, ch) - mystr);
}

size_t nextPowerOf2(size_t n)  
{  
    size_t count = 0;  
      
    if (n && !(n & (n - 1)))  
        return n;  
      
    while( n != 0)  
    {  
        n >>= 1;  
        count += 1;  
    }  
      
    return 1 << count;  
}  