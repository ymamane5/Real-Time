#include <string>
#include <vector>
#include "tokenizer.h"

#ifndef PARSER
#define PARSER

using namespace std;

class parser {

public:
	parser() {}
	~parser() { fs.close(); }
	void copyRow(const string& row);
	void parse(const string filename);

private:
	string row;
	fstream fs;
	//int p_arr[4];

	parser(const parser& p);
	parser& operator=(const parser p);

};

void parser::parse(const string filename)
{
	//cout << "in parse\n";
	tokenizer tok;
	char buffer[100];
	bool endFile;
	fs.open(filename);
	//cout << "in parse2\n";
	
	do {
		endFile = fs.getline(buffer, 100).eof();
		tok.tokenize(string(buffer));
		//cout << buffer << endl;
	} while(!endFile);
}

#endif