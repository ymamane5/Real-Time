#include <string>
#include <vector>
#include <algorithm>
#include <typeinfo>

#ifndef CONTAINER
#define CONTAINER

using namespace std;

class GreaterVal {
public:
	GreaterVal(int i) : val(i) {}
	bool operator()(int* param) const { return (*param == val); }

private:
	int val;
};

template<typename T, typename DTYPE>
class tContainer_t {

public:
	tContainer_t();
	~tContainer_t();
	
	bool operator<(const tContainer_t& cont) const { return (this->data_st.size() < cont.data_st.size()); }
	bool operator==(const tContainer_t& cont) const { return (this->data_st.size() == cont.data_st.size()); }
	bool isEmpty() const { return data_st.empty(); }
	size_t contSize() const { return data_st.size(); }
	void insert(T* elem) { data_st.push_back(elem); }
	const T* getFirst() const { return data_st.front(); }
	const T* getLast() const { return data_st.back(); }
	typename DTYPE::iterator getEnd() const { return data_st.end(); }
	T* find(const T& elem);
	T* removeElement(const T& elem);
	void ramoveAll();
	void deleteElem(const T& elem);
	void deleteAll();
	T* operator[](int index);

	void printData() const;

private:
	tContainer_t& operator=(const tContainer_t&) {}
	tContainer_t(const tContainer_t& cont) {}

	DTYPE data_st;
	typename DTYPE::iterator iter_t;
};

template<typename T, typename DTYPE>
tContainer_t<T, DTYPE>::tContainer_t() { }

template<typename T, typename DTYPE>
tContainer_t<T, DTYPE>::~tContainer_t() 
{
	deleteAll();
}

template<typename T, typename DTYPE>
T* tContainer_t<T, DTYPE>::find(const T& elem)
{
	
	iter_t = find_if(data_st.begin(), data_st.end(), GreaterVal(elem));
	
	if (iter_t == data_st.end())
		return nullptr;
	else
		return *iter_t;
}

template<typename T, typename DTYPE>
T* tContainer_t<T, DTYPE>::removeElement(const T& elem)
{
	T* res;
	
	res = find(elem);
	if (iter_t != data_st.end())
	{
		data_st.erase(iter_t);
	}
	
	return res;
}

template<typename T, typename DTYPE>
void tContainer_t<T, DTYPE>::ramoveAll()
{
	data_st.erase(data_st.begin(), data_st.end());
}

template<typename T, typename DTYPE>
void tContainer_t<T, DTYPE>::deleteElem(const T& elem)
{
	T* res = find(elem);

	if (res != NULL)
	{
		removeElement(*res);
		free(res);
	}
}

template<typename T, typename DTYPE>
void tContainer_t<T, DTYPE>::deleteAll()
{
	for (T* i : data_st)
	{
		free(i);
	}
	ramoveAll();
}

template<typename T, typename DTYPE>
T* tContainer_t<T, DTYPE>::operator[](int index)
{
	if (index >= data_st.size())
	{
		throw 1;
	}
	
	if (typeid(DTYPE) == typeid(vector<int*>))
	{
		return data_st[index];
	}
	else
	{
		iter_t = data_st.begin();
		for (int i = 0; i < index; i++, iter_t++);
		return *iter_t;
	}
}

template<typename T, typename DTYPE>
void tContainer_t<T, DTYPE>::printData() const
{
	for (T* i : data_st)
	{
		cout << *i << endl;
	}
}

#endif