#ifndef STR
#define STR

#include<stdlib.h>
#include<iostream>

using namespace std;

class string_t {

public:
	string_t();
	string_t(const char*);
	string_t(const string_t &str);
	~string_t();

	string_t& operator=(const string_t &str);
	int length() const;
	void setstring(const char* str);
	char* getstring() const;
	int compare(const string_t& str) const;
	void print() const;
	void mytoupper();
	void mytolower();
	void prepend(const char* str);
	void prepend(string_t& str);
	string_t& operator+=(const string_t& str);
	bool operator<(const string_t& str) const;
	bool operator>(const string_t& str) const;
	bool operator>=(const string_t& str) const;
	bool operator<=(const string_t& str) const;
	bool operator==(const string_t& str) const;
	bool operator!=(const string_t& str) const;
	bool contains(const string_t& str) const;
	char operator[](int i) const;
	char& operator[](int i);
	size_t setCapacity(size_t size);
	size_t getCapacity() { return capacity; }
	size_t getFirstAccurance(const char ch) const;
	size_t getLastAccurance(const char ch) const;
	string_t& operator()(int start, uint len);

	static bool setCaseSens(bool flag);
	static bool getCaseSens() { return string_t::caseSens; }
	
	
private:
	char* mystr;
	size_t capacity;
	static size_t default_capacity;
	static bool caseSens;

};
ostream& operator<<(ostream& os, string_t& str);
istream& operator>>(istream& is, string_t& str);
size_t nextPowerOf2(size_t n);

#endif