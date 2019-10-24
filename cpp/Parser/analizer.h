#include <vector>
#include <string>

#ifndef ANALIZER
#define ANALIZER

using namespace std;

class analizer {

public:
	analizer() { rowNum = 0; }
	~analizer() {}
	void checkRow(const vector<string> row);

private:
	vector<string> preDefTokens;
	unsigned int rowNum;

	analizer(const analizer& a);
	analizer& operator=(const analizer& a);

};

#endif