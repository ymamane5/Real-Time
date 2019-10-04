#ifndef EX
#define EX

#include <string>

using namespace std;

class TExeption {

public:
	TExeption(int obj, string desciption, string file, int line);
	~TExeption() {}

	void printExeption();

	
private:

	int m_obj;
	string m_description;
	string m_source_file;
	int m_line;
};

#endif // !MANAGER