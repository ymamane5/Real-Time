#include <iostream>
#include <string>
#include <vector>

#ifndef TOKEN
#define TOKEN

using namespace std;

class tokenizer {

public:
	tokenizer() { tokens = new vector<string>; }
	~tokenizer() {}
	vector<string>& tokenize(const string r);

private:
	vector<string> *tokens;

	tokenizer(const tokenizer& t);
	tokenizer operator=(const tokenizer& t) const;

};

vector<string>& tokenizer::tokenize(const string r)
{
	string row = r;
	size_t pos = 0;
	string token;

	//cout << "in tokenize\n";

	while ((pos = row.find(' ')) != string::npos) 
	{
	    token = row.substr(0, pos);
	   // cout << "pos = " << pos << endl;
	    cout << token << endl;
	    row.erase(0, pos + 1);
	}
}

#endif