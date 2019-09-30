#include <string>
#include <iostream>
#include "memoryManager.h"
#include "memPage.h"

memPage::memPage()
{
	curr_pos = 0;
	page_size = memManager::page_size;
	page_string = new string();
}

memPage::memPage(unsigned int size)
{
	curr_pos = 0;
	page_size = size;
	page_string = new string();
}

unsigned int memPage::readData(string& buff, unsigned int length) const
{
	
	// case 1: no data to read
	if (curr_pos >= actualSize()) {
		cout << "no data to read\n";
		return 0;
	}
	// case 2: there is data to read
	buff.assign(*page_string, curr_pos, length);

	return buff.size();
}
unsigned int memPage::readData(string& buff, unsigned int position, unsigned int length) const
{
	// case 1: no data to read
	if (position >= actualSize()) {
		cout << "no data to read\n";
		return 0;
	}
	// case 2: there is data to read
	buff.assign(*page_string, position, length);

	return buff.size();
}

unsigned int memPage::writeData(const string& buff)
{
	return writeData(buff, curr_pos);
}
unsigned int memPage::writeData(const string& buff, unsigned int position)
{
	string temp(buff);

	if (position < 0 || position > page_size)
		return 0;

	unsigned int len = position + temp.size() > page_size ? (page_size - position) : temp.size();
	if (len < temp.size())
		temp.erase(len, temp.size() - len);

	page_string->replace(position, len, temp);
	curr_pos = page_string->size();
	
	return len;
}

bool memPage::setCurrPosition(unsigned int pos)
{
	if (pos <= page_string->size())
	{
		curr_pos = pos;
		return true;
	}
	return false;
}
