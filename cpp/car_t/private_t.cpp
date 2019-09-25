#include<string>
#include<iostream>
#include "private_t.h"
#include "car_t.h"

private_t::private_t()
{
	speed = 0;
	//car_t::setName("private");
}

private_t::private_t(unsigned int capacity)
{
	speed = 0;
	string p = "private";
	car_t::setName(p);
	car_t::setCapacity(capacity);
}

private_t::~private_t() {}