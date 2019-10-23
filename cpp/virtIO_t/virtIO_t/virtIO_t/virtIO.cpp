#include<string>
#include "virtIO.h"

//return fseek(m_fp, 0, SEEK_END);

int virtIO::open(string name, string mode)
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

unsigned long virtIO::fileLength() const
{
	unsigned long curr, len;
	curr = fseek(m_fp, 0, SEEK_CUR);
	len = fseek(m_fp, 0, SEEK_END);
	fseek(m_fp, curr, SEEK_SET);

	return len;

}