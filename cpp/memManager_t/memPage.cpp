#include <string>
#include <iostream>
#include <algorithm>
#include<string.h>
#include "memManager.h"
#include "memPage.h"

memPage::memPage()
{
	curr_pos = 0;
	page_size = memManager::page_size;
	page_string[0] = '\0';
}

memPage::memPage(unsigned int size)
{
	curr_pos = 0;
	page_size = size;
	page_string[0] = '\0';
}

unsigned int memPage::readData(void* buff, unsigned int length) const
{
	
	// case 1: no data to read
	if (curr_pos >= actualSize()) {
		cout << "no data to read\n";
		return 0;
	}
	// case 2: there is data to read
	//buff.assign(*page_string, curr_pos, length);
	

	return readData(buff, curr_pos, length);
}
unsigned int memPage::readData(void* buff, unsigned int position, unsigned int length) const
{
	// case 1: no data to read
	if (position >= actualSize()) {
		cout << "no data to read\n";
		return 0;
	}
	// case 2: there is data to read
	//buff.assign(*page_string, position, length);
	memcpy(buff, (void*)&(page_string[position]), length);

	return strlen((char*)buff);
}

unsigned int memPage::writeData(const void* buff, unsigned int length)
{
	return writeData(buff, length, curr_pos);
}
unsigned int memPage::writeData(const void* buff, unsigned int length, unsigned int position)
{
	memcpy(page_string + curr_pos, buff, length);

	/*
	string temp(buff);

	if (position < 0 || position > page_size)
		return 0;

	unsigned int len = position + temp.size() > page_size ? (page_size - position) : temp.size();
	if (len < temp.size())
		temp.erase(len, temp.size() - len);

	page_string->replace(position, len, temp);
	curr_pos = page_string->size();
	
	return len;
	*/
	return 0;
}

bool memPage::setCurrPosition(unsigned int pos)
{
	if (pos <= strlen(page_string))
	{
		curr_pos = pos;
		return true;
	}
	return false;
}