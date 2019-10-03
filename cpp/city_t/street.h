#include<vector>

#ifndef STREET
#define STREET

using namespace std;

template<class S_T, class B_T>
class street
{

public:
	street();
	street(S_T id);
	~street();
	street<S_T, B_T>& operator=(street<S_T, B_T>& s);

	void setStreetID(S_T id);
	S_T getStreetID();
	void AddBuilding2Street(building<B_T>& build);
	B_T getBuildingCity();
	void printBuildings();

private:
	S_T m_id;
	vector<building<B_T>> buidingList;

};

template<class S_T, class B_T>
street<S_T, B_T>::street() {}


template<class S_T, class B_T>
street<S_T, B_T>::street(S_T id) { m_id = id; }


template<class S_T, class B_T>
street<S_T, B_T>::~street() {}

template<class S_T, class B_T>
street<S_T, B_T>& street<S_T, B_T>::operator=(street<S_T, B_T>& s)
{
	if(this != s){
		m_id = s.m_id;
		buidingList = s.buidingList;
	}

	return *this;
}

template<class S_T, class B_T>
void street<S_T, B_T>::printBuildings()
{
	for(building<B_T> build : buidingList)
		cout << build.getBuidingID() << "\n";
}


template<class S_T, class B_T>
void street<S_T, B_T>::setStreetID(S_T id) { m_id = id; }

template<class S_T, class B_T>
S_T street<S_T, B_T>::getStreetID() { return m_id; }


template<class S_T, class B_T>
void street<S_T, B_T>::AddBuilding2Street(building<B_T>& build) 
{
	buidingList.push_back(build);
}


template<class S_T, class B_T>
B_T street<S_T, B_T>::getBuildingCity() {}


#endif