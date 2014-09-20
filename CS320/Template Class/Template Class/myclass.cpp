#ifndef MYCLASS_CPP
#define MYCLASS_CPP

#include "myclass.h"

template <class T>
void myClass<T>::setData(int iData)
{
	T input;
	length = iData;
	for(int i = 0; i < length; i++)
	{
		cout << "Enter the next element";
		cin >> input;
		data[i] = input;
	}
};

template <class T>
void myClass<T>::printData()
{
	for(int i = 0; i < length; i++)
	{
		cout << data[i] << " ";
	}
	cout << endl;
};





#endif