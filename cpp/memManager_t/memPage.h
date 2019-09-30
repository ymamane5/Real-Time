#ifndef PAGE
#define PAGE
#include "memoryManager.h"

using namespace std;

class memPage : public memManager {

public:
	memPage();
	memPage(unsigned int size);
	~memPage() { delete page_string; }

	bool isEmpty() const { return (page_string->empty()); }
	bool isFull() const { return (page_string->size() == page_size); }
	unsigned int actualSize() const { return page_string->size(); }
	bool setCurrPosition(unsigned int pos);
	unsigned int readData(string& buff, unsigned int length) const;
	unsigned int readData(string& buff,unsigned int position, unsigned int length) const;
	unsigned int writeData(const string& buff);
	unsigned int writeData(const string& buff, unsigned int position);
private:
	memPage(memPage& page);
	string* page_string;
};

#endif // !PAGE