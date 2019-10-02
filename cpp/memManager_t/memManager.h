#ifndef MANAGER
#define MANAGER

#include <string>
#include<string.h>

using namespace std;

class memManager {

public:
	~memManager() {}

	static void setPageSize(unsigned int size) { page_size = size; }
	static unsigned int getPageSize() { return page_size; }

	static void setDefPageSize(unsigned int size) { defualt_page_size = size; }
	static unsigned int getDefPageSize() { return defualt_page_size; }

	virtual bool setCurrPosition(unsigned int pos) = 0;
	unsigned int getCurrPosition() const { return curr_pos; }

	virtual bool isEmpty() const { return 0; }
	virtual unsigned int actualSize() const { return 0; }

	virtual unsigned int readData(void* buff, unsigned int length) const { return 0; }
	virtual unsigned int readData(void* buff, unsigned int position, unsigned int length) const { return 0; }
	virtual unsigned int writeData(const void* buff, unsigned int length) { return 0; }
	virtual unsigned int writeData(const void* buff, unsigned int length, unsigned int position) { return 0; }
protected:
	
	unsigned int curr_pos;
	static unsigned int page_size;
	static unsigned int defualt_page_size;	
};

#endif // !MANAGER