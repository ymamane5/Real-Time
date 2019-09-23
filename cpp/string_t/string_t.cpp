#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "string_t.h"

string_t::string_t()
{
	mystr[0] = 0;
}

string_t::string_t(char* str)
{
	strcpy(mystr, str);
}

string_t::string_t(const string_t& str)  // copy ctor
{
	setstring(str.getstring());
}

string_t::~string_t()
{
	free(mystr);
}

string_t& string_t::operator=(const string_t& str)
{
	strcpy(mystr, str.getstring());

	return *this;
}

int string_t::length()
{
	int i;

	for(i = 0; mystr[i] != '\0'; i++);

	return i;
}

void string_t::setstring(char* str)
{
	strcpy(mystr, str);
}

char* string_t::getstring() const
{
	return mystr;
}