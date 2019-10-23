#include<stdio.h>

#ifndef VIRT
#define VIRT

using namespace std;

class virtIO {

public:
	enum statusType {ok, cant_open_file, bad_access, writeEror, readEror};

	virtIO() {};
	~virtIO() { fclose(m_fp); };

	template<class T>
	int getFormat(T& val, char* f);
	int open(string name, string mode);
	string getPath() const { return m_path; };
	virtual string getMode() const = 0;
	unsigned long fileLength() const;
	unsigned long getPosition() const { return ftell(m_fp); };
	void setPosition(unsigned long pos) { fseek(m_fp, pos, SEEK_SET); };


protected:
	FILE* m_fp;
	string m_path;
	unsigned long m_position;
	string m_mode;
	enum statusType m_status;

	//virtual virtIO& operator>>(int& num) = 0; // read
	//virtual virtIO& operator<<(int num) = 0;  // write


private:
	virtIO(const virtIO& v);
	virtIO& operator=(const virtIO& v);

};

template<class T>
int virtIO::getFormat(T& val, char* f)
{
	if (typeid(val) == typeid(int))
	{
		strcpy(f, "%d");
	}
	else if (typeid(val) == typeid(float))
	{
		strcpy(f, "%f");
	}
	else if (typeid(val) == typeid(char))
	{
		strcpy(f, "%c");
	}
	else if (typeid(val) == typeid(short))
	{
		strcpy(f, "%hi");
	}
	else if (typeid(val) == typeid(long))
	{
		strcpy(f, "%ld");
	}
	else if (typeid(val) == typeid(double))
	{
		strcpy(f, "%lf");
	}
	else
		return -1;

	return 1;
}

#endif