#include <string>
#include <vector>

#ifndef TOKEN
#define TOKEN

using namespace std;

class tokenizer {

public:
	tokenizer() { tokens = new vector<string>; }
	~tokenizer() {}
	vector<string>& tokenize(string row);

private:
	vector<string> tokens;

	tokenizer(const tokenizer& t);
	tokenizer& operator=(const tokenizer& t);

};

vector<string>& tokenizer::tokenize(string row)
{
	// stringstream class check1 
    stringstream check1(line); 
      
    string intermediate; 
      
    // Tokenizing w.r.t. space ' ' 
    while(getline(check1, intermediate, ' ')) 
    { 
        tokens.push_back(intermediate); 
    } 
      
    // Printing the token vector 
    for(int i = 0; i < tokens.size(); i++) 
        cout << tokens[i] << '\n'; 
}

#endif