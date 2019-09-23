#ifndef STR
#define STR

#include<stdlib.h>
#define SIZE 100

class string_t {
//	#include<stdio.h>
//	#include<stdlib.h>
public:
	string_t();
	string_t(char*);
	string_t(const string_t &str);
	~string_t();
	string_t& operator=(const string_t &str);
	int length();
	void setstring(char* str);
	char* getstring() const;
	//int compare(string_t& str);
	//void print();


private:
	char* mystr = new string::string();
};

#endif