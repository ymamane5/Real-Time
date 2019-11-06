#include <iostream>
#include <string>
#include <fstream>
#include "parser.h"
#include "tokenizer.h"
#include "analizer.h"

using namespace std;

int main(int argc, char const *argv[])
{
	parser p;
	tokenizer t;

	if(argc < 2)
	{
		cout << "no file entered\n";
		return 0;
	}

	p.parse(string(argv[1]));
	
	return 0;
}