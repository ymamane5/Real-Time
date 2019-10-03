#include<vector>

#ifndef CITY
#define CITY

using namespace std;

template<class C_T, class S_T, class B_T>
class city
{
public:
	city();
	city(C_T id);
	~city();
	city<C_T, S_T, B_T>& operator=(city<C_T, S_T, B_T>& c);

	void setCityID(C_T id);

private:
	C_T m_id;
	vector<S_T> streetList;
};

template<class C_T, class S_T, class B_T>
city<C_T, S_T, B_T>::city() {}


template<class C_T, class S_T, class B_T>
city<C_T, S_T, B_T>::city(C_T id) { m_id = id; }


template<class C_T, class S_T, class B_T>
city<C_T, S_T, B_T>::~city() {}

template<class C_T, class S_T, class B_T>
city<C_T, S_T, B_T>& city<C_T, S_T, B_T>::operator=(city<C_T, S_T, B_T>& c)
{
	if(this != c)
		m_id = c.m_id;

	return *this;
}

template<class C_T, class S_T, class B_T>
void city<C_T, S_T, B_T>::setCityID(C_T id) { m_id = id; }

#endif