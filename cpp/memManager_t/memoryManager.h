#ifndef MANAGER
#define MANAGER

#include <string>

using namespace std;

class memManager {

public:
	static void setPageSize(unsigned int size) { page_size = size; }
	static unsigned int getPageSize() { return page_size; }

	static void setDefPageSize(unsigned int size) { defualt_page_size = size; }
	static unsigned int getDefPageSize() { return defualt_page_size; }

	virtual bool setCurrPosition(unsigned int pos) { return 0; }
	unsigned int getCurrPosition() const { return curr_pos; }

	virtual bool isEmpty() const { return 0; }
	virtual unsigned int actualSize() const { return 0; }

	virtual unsigned int readData(string& buff, unsigned int length) const { return 0; }
	virtual unsigned int readData(string& buff, unsigned int position, unsigned int length) const { return 0; }
	virtual unsigned int writeData(const string& buff) { return 0; }
	virtual unsigned int writeData(const string& buff, unsigned int position) { return 0; }
protected:
	~memManager() {}
	
	unsigned int curr_pos;
	static unsigned int page_size;
	static unsigned int defualt_page_size;	
};

#endif // !MANAGER