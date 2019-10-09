#include <string>
#include <vector>
#include <list>
#include <iostream>
#include "tContainer_t.h"

using namespace std;

int main()
{
	int input, val;
	int* res = NULL;
	tContainer_t<int, vector<int*> > cont;
	tContainer_t<int, list<int*> > cont2;

	do {
		cout << "choose option:\n1. insert elements\n2. check if empty\n3. num of elements\n4. first element" << endl;
		cout << "5. last element\n6. find element\n7. remove element\n8. remove all elements\n9. delete element" << endl;
		cout << "10. delete all\n11. print data\n12. operator[]\n13. exit" << endl;
		cin >> input;

		switch (input)
		{
		case 1:
			cout << "enter value:\n";
			cin >> val;
			cont.insert(new int(val));
			break;
		case 2:
			if (cont.isEmpty())
				cout << "Empty" << endl;
			else
				cout << "not empty" << endl;
			break;
		case 3:
			cout << cont.contSize() << endl;
			break;
		case 4:
			cout << *cont.getFirst() << endl;
			break;
		case 5:
			cout << *cont.getLast() << endl;
			break;
		case 6:
			cout << "enter value:\n";
			cin >> val;
			res = cont.find(val);
			if (res == NULL)
				cout << "value not found" << endl;
			else
				cout << "found: " << *res << endl;
			
			break;
		case 7:
			cout << "enter value:\n";
			cin >> val;
			res = cont.removeElement(val);
			if (res == NULL)
				cout << "remove failed - cant find element" << endl;
			else
				cout << "removed element: " << *res << endl;
			break;
		case 8:
			cont.ramoveAll();
			break;
		case 9:
			cout << "enter value:\n";
			cin >> val;
			cont.deleteElem(val);
			cout << "element deleted" << endl;
			break;
		case 10:
			cont.deleteAll();
			break;
		case 11:
			cont.printData();
			break;
		case 12:
			cout << "enter index:\n";
			cin >> val;
			try {
				cout << "element = " << *cont[val] << endl;
			}
			catch (int ex) {
				cout << "Eror: index out of bound\n";
			}
			break;
		default:
			break;
		}

	} while (input < 13);

	return 0;
}