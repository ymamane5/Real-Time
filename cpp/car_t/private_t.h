#ifndef PRIVATE
#define PRIVATE 

#include "car_t.h"



class private_t : public car_t {

public:
	private_t();
	private_t(unsigned int capacity);
	~private_t();
	void accelerate() { speed += 10; }
	void reduceSpeed() { speed -= 10; }

private:
	int speed;
};

#endif