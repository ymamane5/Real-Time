#include<stdio.h>

#ifndef VIRT
#define VIRT

//enum modeType {r, w, rplus, wplus}; // br, bw, brplus, bwplus
enum statusType {ok, cant_open_file, bad_access, writeEror, readEror};

using namespace std;

class virtIO {

public:
	virtIO() {};
	~virtIO() {};

	virtual int open(string name, string mode) = 0;
	string getPath() const { return m_path; };
	string getMode() const { return m_mode; };
	unsigned long fileLength() const;
	unsigned long getPosition() const { return ftell(m_fp); };
	void setPosition(unsigned long pos) { m_position = pos; };


protected:
	FILE* m_fp;
	string m_path;
	unsigned long m_position;
	string m_mode;
	enum statusType m_status;

	virtual virtIO& operator>>(int& num) = 0; // read
	virtual virtIO& operator<<(int num) = 0;  // write


private:
	virtIO(const virtIO& v);
	virtIO& operator=(const virtIO& v);

};

#endif