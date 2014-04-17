/*
By: Chris Arnold


This is Part 2 of Assignment 1. We are developing our own string class
The main function just creates instances of the class and tests the included functions.

Program Compiles, during runtime it completes every line of code properly until the destructors for s1, which fails
s2 isn't reached. s3 and s4 free themselves.


*/

#include "MyString.h"
#include <iostream>


using namespace std;

int main()
{
	MyString s1;						//creating instances of MyString using the different constructors
	MyString s2 = "Pepperoni";
	MyString s3 = "Pizza";
	MyString s4(s2);
										//Verifying constructors work
	cout << "The value of MyString s1 with default constructor is: "; s1.Put();
	cout << endl << "The value of MyString s2, copy contructor of a cstring: "; s2.Put();
	cout << endl << "The value of MyString s4, initialized with the contents of s2: "; s4.Put();
	cout << endl << "Now lets test the operator overloading. Testing s2 + s3........" << endl << "s2 now contains: ";
	s2 + s3; s2.Put();
	cout << endl << "And now testing s1 = s2....." << endl << "s1 now contains: ";
	s1 = s2; s1.Put();
	cout << endl << "And Finally we will Test the reverse function. The reverse of s1 is: ";
	s1.Reverse(); s1.Put();
	cout << endl << "That is all. The program will now automatically call the destructor functions. Freeing memory. " << endl;


	return 0;
}