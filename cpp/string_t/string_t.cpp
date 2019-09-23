#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <ctype.h>
#include<iostream>
#include "string_t.h"

using namespace std;

string_t::string_t()
{
	mystr = new char[32];
}

string_t::string_t(const char* str)
{
	mystr = new char[32];
	strcpy(mystr, str);
}
string_t::string_t(const string_t &str)  // copy ctor
{
	mystr = new char[32];
	setstring(str.getstring());
}

string_t::~string_t()
{
	delete[] mystr;
}

void string_t::createString(const char* str)
{
	delete[] mystr;
	mystr = new char[32];
	strcpy(mystr, str);
}

string_t& string_t::operator=(const string_t& str)  // str1 = str2
{
	if(this != &str)
	{
		createString(str.getstring());
	}

	return *this;
}

int string_t::length() const
{
	return strlen(mystr);
}

void string_t::setstring(const char* str)
{
	createString(str);
}

char* string_t::getstring() const
{
	return mystr;
}

int string_t::compare(const string_t& str) const
{
	return strcmp(mystr, str.mystr);
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
	char temp[32];

	strcpy(temp, mystr);
	createString(str);
	strcat(mystr, temp);
}

void string_t::prepend(string_t& str)
{
	char temp[32];

	strcpy(temp, mystr);
	createString(str.getstring());
	strcat(mystr, temp);
}

void string_t::operator+=(const string_t& str)
{
	strcat(mystr, str.mystr);
}

int string_t::operator<(const string_t& str) const
{
	return strcmp(str.mystr, this->mystr);
}
int string_t::operator>(const string_t& str) const
{
	return strcmp(this->mystr, str.mystr);
}

bool string_t::operator>=(const string_t& str) const
{
	if(strcmp(this->mystr, str.mystr) >= 0)
		return true;
	else
		return false;
}
bool string_t::operator<=(const string_t& str) const
{
	if(strcmp(this->mystr, str.mystr) <= 0)
		return true;
	else
		return false;
}
bool string_t::operator==(const string_t& str) const
{
	if(strcmp(this->mystr, str.mystr) == 0)
		return true;
	else
		return false;
}
bool string_t::operator!=(const string_t& str) const
{
	if(strcmp(this->mystr, str.mystr) != 0)
		return true;
	else
		return false;
}

bool string_t::contains(const string_t& str) const
{
	if(strstr(this->mystr, str.mystr) != NULL)
		return true;
	else
		return false;
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
/*
ostream& string_t::operator<<(ostream& os, string_t& str)
{
	os << str.mystr << "\n";
	return os;
}
*/
