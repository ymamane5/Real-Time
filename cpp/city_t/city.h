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
	C_T getCityID();
	void AddStreet(street<S_T, B_T>& s);
	street<S_T, B_T>& getStreet(S_T id);
	void printStreets();

private:
	C_T m_id;
	vector<street<S_T, B_T>> streetList;
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
	if(this != c){
		m_id = c.m_id;
		streetList = c.streetList;
	}

	return *this;
}

template<class C_T, class S_T, class B_T>
void city<C_T, S_T, B_T>::printStreets()
{
	for(street<S_T, B_T> s : streetList)
		s.printBuildings();
		
}

template<class C_T, class S_T, class B_T>
void city<C_T, S_T, B_T>::setCityID(C_T id) { m_id = id; }

template<class C_T, class S_T, class B_T>
C_T city<C_T, S_T, B_T>::getCityID() { return m_id; }

template<class C_T, class S_T, class B_T>
void city<C_T, S_T, B_T>::AddStreet(street<S_T, B_T>& s)
{
	streetList.push_back(s);
}

template<class C_T, class S_T, class B_T>
street<S_T, B_T>& city<C_T, S_T, B_T>::getStreet(S_T id)
{
	try{
		for(street<S_T, B_T> s : streetList)
		{
			if(s.getStreetID() == id)
				return s;
		}
		throw 1;
	}

	catch(int ex){
		cout << "Eror: cannot find requested street\n";
	}
}


#endif