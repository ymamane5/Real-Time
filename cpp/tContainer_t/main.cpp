#include <string>
#include <vector>
#include <iostream>
#include "tContainer_t.h"

int main()
{
	int i = 5;

	tContainer_t<int, vector<int*> > cont;
	cont.insert(&i);
	cout << cont.isEmpty() << endl;
	cout << *cont.getFirst() << endl;

	return 0;
}