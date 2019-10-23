#include<string>
#include "virtIO.h"
#include "asciiIO.h"

int asciiIO::open(string name, string mode)
{
	m_fp = fopen(name.c_str(), mode.c_str());
	if(m_fp == NULL)
	{
		printf("cannot open file\n");
		m_status = cant_open_file;
		return 0;
	}
	
	m_path = name;
	m_position = 0;
	m_mode = mode;
	m_status = ok;	

	return 1;
}

virtIO& asciiIO::operator>>(int& num) // read
{
	if(m_mode == "r" || m_mode == "r+")
	{
		fscanf(m_fp, "%d", &num);
		return *this;
	}
}

virtIO& asciiIO::operator<<(int num)  // write
{
	if(m_mode == "w" || m_mode == "w+" || m_mode == "r+")
	{
		fprintf(m_fp, "%d", num);
		m_position = ftell(m_fp);
		return *this;
	}
	else  //ex
	{
		printf("no premossion to write\n");
		m_status = bad_access;
		return *this;
	}
}