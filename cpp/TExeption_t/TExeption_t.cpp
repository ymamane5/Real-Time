#include<iostream>
#include "TExeption_t.h"

TExeption::TExeption(int obj, string desciption, string file, int line)
{
	m_obj = obj;
	m_description = desciption;
	m_source_file = file;
	m_line = line;
}

void TExeption::printExeption()
{
	cout << "ex num = " << m_obj << "\ndescription = " << m_description;
	cout << "\nfile = " << m_source_file << "\nline = " << m_line << "\n";
}