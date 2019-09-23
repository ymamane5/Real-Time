#ifndef STR
#define STR

#include<stdlib.h>
class string_t {

#include<iostream>

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
	void operator+=(const string_t& str);
	int operator<(const string_t& str) const;
	int operator>(const string_t& str) const;
	bool operator>=(const string_t& str) const;
	bool operator<=(const string_t& str) const;
	bool operator==(const string_t& str) const;
	bool operator!=(const string_t& str) const;
	bool contains(const string_t& str) const;
	char operator[](int i) const;
	char& operator[](int i);
	//ostream& operator<<(ostream& os, string_t& str);

private:
	char* mystr;
	void createString(const char* str);
};

#endif