/*
CS 210, Assignment #2 October 13, 2011
Chris Arnold
200276366
*/
#include <iostream>

using namespace std;


class myFraction
{
private:
	int numerator, denominator;
public:
	myFraction();				//Set fraction to 0/1
	void printFraction();		//print to screen fraction in - numerator/denominator - format
	void setFraction(int num, int den);			//sets the numerator and denominator of fraction(users input)
	bool operator>(myFraction frac);			//compares to fractions. Returns true or false depending on which is larger
	myFraction operator+(myFraction frac);		//Adds two fractions together. Reterns Sum
	void operator=(myFraction frac);			//make's one fraction equal to another
	myFraction operator-(myFraction frac);		//Subtracts two fractions. Returns difference.
	myFraction operator*(myFraction frac);		//Multiplies two fractions. Returns product
	myFraction operator*(int number);			//Mulitplies a fraction by an integer. returns product.
	friend myFraction operator*(int number, myFraction frac);		//multiplies an integer by a fraction. returns a fraction.
};



