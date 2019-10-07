#include <string>
#include <vector>

#ifndef CONTAINER
#define CONTAINER

using namespace std;

template<typename T, typename DTYPE>
class tContainer_t {

public:
	tContainer_t();
	~tContainer_t();
	
	bool operator<(const tContainer_t&) const;
	bool operator==(const tContainer_t&) const;
	bool isEmpty() const { return data_st.empty(); }
	size_t contSize() const { return data_st.size(); }
	void insert(T* elem) { data_st.push_back(elem); }
	const T* getFirst() const { return data_st.front(); }
	const T* getLast() const { return data_st.back(); }
	const T* find(T& elem);


private:
	tContainer_t& operator=(const tContainer_t&);
	tContainer_t(const tContainer_t& cont);

	DTYPE data_st;
	typename DTYPE::iterator iter_t;

};

template<typename T, typename DTYPE>
tContainer_t<T, DTYPE>::tContainer_t() { iter_t = data_st.begin(); }

template<typename T, typename DTYPE>
tContainer_t<T, DTYPE>::~tContainer_t() {}

template<typename T, typename DTYPE>
T* tContainer_t<T, DTYPE>::find(T& elem)
{

}

#endif