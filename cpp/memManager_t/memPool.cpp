#include <iostream>
#include<string.h>
#include "memManager.h"
#include "memPool.h"
#include "memPage.h"

using namespace std;

memPool::memPool()
{
	v.push_back(new memPage());
	curr_pos = 0;
	page_size = memManager::page_size;
}

memPool::~memPool()
{
	int i;
	for (i = 0; i < v.size(); i++) {
		delete v[i];
	}
}

bool memPool::isEmpty() const
{
	if (v.size() == 0  || (v.size() == 1 && v.at(0)->isEmpty()))
		return true;
	else
		return false;
}

bool memPool::setCurrPosition(unsigned int pos)
{
	
	if (pos > actualSize())
	{
		throw 1;
	}
	
	curr_pos = pos;

	return true;
}

unsigned int memPool::readData(void* buff, unsigned int length) const
{
	return readData(buff, curr_pos, length);
}
unsigned int memPool::readData(void* buff, unsigned int position, unsigned int length) const
{
	char* temp_buff = new char[page_size];
	unsigned int page_num = position / page_size;
	unsigned int offset = position % page_size;
	unsigned int bytes_read = 0, new_length;

	// case 1: no data to read
	if (position >= actualSize()) {
		cout << "no data to read\n";
		return 0;
	}
	// case 2: there is data to read
	bytes_read = v[page_num]->readData(buff, offset, length);
	offset = 0;

	while (bytes_read < length)
	{
		page_num++;
		//new_length = (v[page_num]->actualSize()) < length ? (v[page_num]->actualSize() - bytes_read) : length - bytes_read;
		new_length = length -bytes_read;
		bytes_read += v[page_num]->readData(temp_buff, offset, new_length);
		//buff.append(temp_buff);
		strcat((char*)buff, temp_buff);
	}
	delete[] temp_buff;
	return strlen((char*)buff);
}

unsigned int memPool::writeData(const void* buff, unsigned int length)
{
	return writeData(buff, length, curr_pos);
}
unsigned int memPool::writeData(const void* buff, unsigned int length, unsigned int position)
{
	unsigned int page_num = position / page_size;
	unsigned int offset = position % page_size;
	unsigned int bytes_written = 0;
	char* substr = new char[page_size];

	if (position < 0 || position > actualSize())
		return 0;

	bytes_written = v[page_num]->writeData(buff, length);
	position += bytes_written;

	while (bytes_written < strlen((char*)buff))
	{
		v.push_back(new memPage());
		page_num++;
		offset = 0;
		//substr = buff.substr(bytes_written, (strlen(buff) - bytes_written));
		bytes_written += v[page_num]->writeData((char*)buff + bytes_written, offset);
	}
	curr_pos += bytes_written;
	delete[] substr;
	return bytes_written;
}