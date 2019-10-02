#ifndef PAGE
#define PAGE
#include "memManager.h"

using namespace std;

class memPage : public memManager {

public:
	memPage();
	memPage(unsigned int size);
	~memPage() { delete page_string; }

	bool isEmpty() const { return (strlen(page_string) == 0); }
	bool isFull() const { return (strlen(page_string) == page_size); }
	unsigned int actualSize() const { return strlen(page_string); }
	bool setCurrPosition(unsigned int pos);
	unsigned int readData(void* buff, unsigned int length) const;
	unsigned int readData(void* buff,unsigned int position, unsigned int length) const;
	unsigned int writeData(const void* buff, unsigned int length);
	unsigned int writeData(const void* buff, unsigned int length, unsigned int position);
private:
	memPage(memPage& page);
	char* page_string;
};

#endif // !PAGE