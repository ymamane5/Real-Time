#include<string>
#include<iostream>
#include "building.h"
#include "street.h"
#include "city.h"

using namespace std;

int main()
{
	building<int> build1(1);
	building<int> build2(2);
	street<int, int> myStreet(10);

	myStreet.AddBuilding2Street(build1);
	myStreet.AddBuilding2Street(build2);


	cout << "builing id = " << build1.getBuidingID() << "\n";
	cout << "builing id = " << build2.getBuidingID() << "\n";
	myStreet.printBuildings();



	return 0;
}