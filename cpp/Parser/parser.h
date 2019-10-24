#include <string>
#include <vector>
#include "tokenizer.h"

#ifndef PARSER
#define PARSER

using namespace std;

class parser {

public:
	parser() {}
	~parser() {}
	void copyRow(const string& row);
	void parse(const string filename);

private:
	string row;
	//int p_arr[4];

	parser(const parser& p);
	parser& operator=(const parser p);

};

void parser::parse(const string filename)
{
	fstream fs;
	tokenizer tok;
	char buffer[100];
	bool endFile;

	fs.open(filename);
	
	do {
		endFile = fs.getline(buffer, 100).eof();
		tok.tokenize(string(buffer));
		cout << buffer << endl;
	} while(!endFile);

	fs.close();
}

#endif