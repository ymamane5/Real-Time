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
	city<string, int , int> myCity("myCity1");

	myStreet.AddBuilding2Street(build1);
	myStreet.AddBuilding2Street(build2);
	myCity.AddStreet(myStreet);

	myCity.printStreets();

	cout << "city = " << myCity.getCityID() << "\n";
	myCity.getStreet(10);


	return 0;
}