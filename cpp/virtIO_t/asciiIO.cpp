#include<string>
#include "virtIO.h"
#include "asciiIO.h"

asciiIO& asciiIO::operator>>(int& num) // read
{
	if(m_mode == "r" || m_mode == "r+")
	{
		fscanf(m_fp, "%d", &num);
	}
	else
		m_status = readEror;

	return *this;
}

asciiIO& asciiIO::operator<<(int num)  // write
{
	if(m_mode == "w" || m_mode == "w+" || m_mode == "r+")
	{
		fprintf(m_fp, "%d", num);
		m_position = ftell(m_fp);
	}
	else  //ex
	{
		printf("no premossion to write\n");
		m_status = writeEror;
	}

	return *this;
}