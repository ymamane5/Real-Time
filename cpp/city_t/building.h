#ifndef BUILD
#define BUILD

template<class B_T>
class building
{
public:
	building();
	building(B_T id);
	~building();
	building& operator=(building& b);
	
	void setBuidingID(B_T id);
	B_T getBuidingID();

private:
	B_T m_id;
};

template<class B_T>    //CTOR
building<B_T>::building() {}

template<class B_T>    //CTOR
building<B_T>::building(B_T id)
{
	m_id = id;
}

template<class B_T>    //DTOR
building<B_T>::~building() {}

template<class B_T> 
building<B_T>& building<B_T>::operator=(building<B_T>& b)
{
	if(this != b)
		m_id = b.m_id;

	return *this;
}

template<class B_T>
void building<B_T>::setBuidingID(B_T id) { m_id = id; }


template<class B_T>
B_T building<B_T>::getBuidingID() { return m_id; }


#endif