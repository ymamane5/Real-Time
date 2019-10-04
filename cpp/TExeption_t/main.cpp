#include<iostream>
#include<string>
#include "TExeption_t.h"

int main()
{
	int i = 1;

	try {
		if (i == 1)
			throw new TExeption(1, "test_exeption", __FILE__, __LINE__);
	}
	catch (TExeption* ex) {
		ex->printExeption();
	}

}