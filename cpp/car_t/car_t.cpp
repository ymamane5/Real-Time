#include<string>
#include<iostream>
#include "car_t.h"

unsigned int car_t::did = 0;

car_t::car_t():id(did++), gear_t(manual), engine_capacity(1000)
{
	//name = ""; 
}

car_t::car_t(unsigned int e_capacity):id(did++), gear_t(manual), engine_capacity(e_capacity)
{
	//name = ""; 
}

car_t::~car_t(){}

car_t& car_t::operator=(car_t& car)
{

}

bool car_t::operator<(car_t& car)
{
	if(this->engine_capacity < car.engine_capacity)
		return true;
	else
		return false;
}

bool car_t::sameType(car_t& car)
{
	if(this->name.compare(car.name))
		return true;
	else
		return false;
}