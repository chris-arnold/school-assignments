#ifndef MYCLASS_H
#define MYCLASS_H
#include <iostream>
using namespace std;

template <class T>
class myClass
{
private:
	T data[100];
	int length;
public:
	void setData(int iLength);
	void printData();

};
#endif
#include "myClass.cpp"