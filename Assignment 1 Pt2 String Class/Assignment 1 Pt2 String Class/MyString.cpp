#ifndef MYSTRING_CPP
#define MYSTRING_CPP

#include <iostream>
#include "MyString.h"

using namespace std;

/*
Input - nothing
initiate length to 0, and initialize the array
output - nothing
*/
MyString::MyString()
{
	length = 0;						//initializing array to size of 0. Will later be overwritten
	pData = new char[NULL];
	pData[length] = '\0';
}
/*
Input - c-string
copy this c-string into MyString. update critical value in MyString
output - returns nothing.
*/
MyString::MyString(char *cString)			//copy constructor of an existing c-string
{
	length = strlen(cString);				//using build in function to get the length of string we are copying
	this->pData = new char[length + 1];				//creating are array of the appropriate length to hold the c-string
	for (int i = 0; i < length; i++)		//copying array contents one by one
	{
		pData[i] = cString[i]; 
	}
	pData[length] = '\0';
}

/*
Input - MyString
initialize MyString to the same values of the inputed MyString
OutPut - nothing
*/
MyString::MyString(MyString const& s)		//we already have MyString just need to copy. Will copy one element at a time until NULL
{
	length = s.length;							//our cstring will be at least one character long
	this->pData = new char[length + 1];					
	for (int i = 0; i < length; i++)
	{
		pData[i] = s.pData[i];				//copying passed mystring into curret cstring
	}
	pData[length] = '\0';					//adding null character to end of array
}


/*
Input - nothing
de-allocate memory
Output - nothing
*/
MyString::~MyString()			//deletes dynamic array and deletes references to it
{	
	if (pData != NULL)
	{
	delete [] pData;
	pData = NULL; 
	length = NULL;
	}
}

/*
Input - MyString - constant we do(MyString1 = MyString2)
We assign the inputed MyString2 to MyString1. Update length of MyString1. Copy element by element
Output - MyString1
*/
MyString& MyString::operator=(MyString const& s)
{
	length = s.length;
	for (int i = 0; i < s.length; i++)
	{
		this->pData[i] = s.pData[i];
	}
	pData[length] = '\0';

	return *this;
}

/*
Input - MyString constant
Get Length of left and right side arrays. Add them together to get the new length. Update length in left side array. 
Add the characters from the right side array to the end of the left side array. Add terminating character to end of
array.
Output - Return the left side array, which is now leftside + rightside
*/
MyString& MyString::operator+(MyString const& s)
{
	int lLength = length;
	length = lLength + s.length;
	for (int i = lLength; i < length; i++)
	{
			this->pData[i] = s.pData[i-lLength];
	}
	this->pData[length] = '\0';

	return *this;
}

/*
Input - Nothing
Output - pData at indicated element until termination character is met
*/
void MyString::Put()
{
	for(int i = 0; pData[i] != '\0'; i++)
	{
		cout << pData[i];
	}
}

/*
Input - Nothing
Reverse function. Create a temp value to hold value to be swapped. -1 from length to account for termination character. Swap 0 with max.
Increment low value. Decrement High Value. Check to see that high-low is >=1. If true continue. Else Exit. Rinse. Repeat.
output - Nothing
*/
void MyString::Reverse()
{
	int max = length - 1;				//dont want to be moving the null character
	char temp = NULL;
	for(int i = 0; (max - i) >= 1; i++)
	{
		temp = pData[i];
		this->pData[i] = this->pData[max];
		this->pData[max] = temp;
		max--;
	}
}



#endif
