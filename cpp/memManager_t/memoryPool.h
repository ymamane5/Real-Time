#ifndef POOL
#define POOL

#include "memPage.h"
#include "memoryManager.h"
#include <vector>

using namespace std;

class memPool : public memManager {
public:
	memPool();
	~memPool();

	bool isEmpty() const;
	bool setCurrPosition(unsigned int pos);
	unsigned int actualSize() const { return (v.size() - 1) * page_size + (v.back()->actualSize()); }
	unsigned int readData(string& buff, unsigned int length) const;
	unsigned int readData(string& buff, unsigned int position, unsigned int length) const;
	unsigned int writeData(const string& buff);
	unsigned int writeData(const string& buff, unsigned int position);

private:
	memPool(memPool&);  // copy is not possible
    vector<memPage*> v; 
};		 
	
#endif // !POOL