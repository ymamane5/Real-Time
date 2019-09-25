#ifndef CAR
#define CAR 

#include<string>

using namespace std;
enum gearType {manual, automatic};

class car_t {

public:
	car_t();
	car_t(unsigned int e_capacity);
	
	
protected:
	~car_t();
	car_t(car_t& car);  // copy CTOR

	void setName(string& _name) { name.assign(_name); }
	string getName() { return name; }
	car_t& operator=(car_t& car);
	bool operator<(car_t& car);
	bool sameType(car_t& car);
	void setCapacity(unsigned int capacity) { engine_capacity = capacity; }

	//void setGearType(enum gearType gear) { gear_t = gear; }
	//enum gearType getGearType() { return gear_t; }

private:

	const unsigned int id;
	string name;
	const enum gearType gear_t;
	unsigned int engine_capacity;

	static unsigned int did;
	
};

#endif