#ifndef CLASSINFO_H
#define CLASSINFO_H
#include "unsortedList.h"

const int numberOfClasses = 10;

struct classInfo
{
	unsortedList cookies;
	int classID;
	int totalSoldCookies;

};


#endif