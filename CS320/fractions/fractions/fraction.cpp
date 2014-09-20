/*
CS 210, Assignment #2 October 13, 2011
Chris Arnold
200276366
*/
#include "fraction.h"

/*Simply setting the fraction to 0/1 which is 0.*/
myFraction::myFraction()
{
	numerator = 0;
	denominator = 1;
};

/* We are printing the function. Just outputting the numerator and denominator with a / inbetween */
void myFraction::printFraction()
{
	cout << numerator << "/" << denominator;
};

/*Set Fraction - We take in 2 integers corresponding to the numerator and the denominator. These values are
then written into the class data and function exited. 
NOTE: This function checks for a denominator of zero, 
but does not attempt to fix it. The data must be checked before sending into the function.*/
void myFraction::setFraction(int num, int den)
{
	numerator = num;
	if(den == 0)
	{
		cout << "Oops.. This is awkward... Denominator cannot be zero." << endl;
		return;
	}
	else
	{
		denominator = den;
	}
};

/*overloading > operation - we take in an object myFraction and compare it to the member fraction.
Comparison is done by finding a common denominator, then comparing the numerators. Then either true or
false is returned, depending on outcome.
*/
bool myFraction::operator>(myFraction frac)
{
	if (denominator != frac.denominator)
	{
		myFraction temp1, temp2;
		temp2.numerator = frac.numerator * denominator;				//left hand
		temp2.denominator = frac.denominator * denominator;
		temp1.numerator = numerator * frac.denominator;				//right hand
		temp1.denominator = denominator * frac.denominator;
		if(temp1.numerator > temp2.numerator)
			return true;
		else
			return false;
	}
	else 
	{
		if(numerator > frac.numerator)
			return true;
		else
			return false;
	}

};

/*overloading + operator - we take in an object(myFraction) and add that to the member myFraction. 
We then return a temporary myFraction, leaving the initial fractions untouched. Adding is done by
finding a common denominator and adding the numerators. */
myFraction myFraction::operator+(myFraction frac)
{
	myFraction temp;
	if (denominator != frac.denominator)
	{
		myFraction temp1, temp2;
		temp1.numerator = frac.numerator * denominator;				//right hand
		temp1.denominator = frac.denominator * denominator;
		temp2.numerator = numerator * frac.denominator;				//left hand
		temp2.denominator = denominator * frac.denominator;
		temp.numerator = temp2.numerator + temp1.numerator;
		temp.denominator = temp1.denominator;
	}
	else
	{
		temp.numerator = numerator + frac.numerator;
		temp.denominator = denominator;
	}
	return temp;
};

/*overloading the = operator - we take in a myFraction object and want to set that to the member
fraction. We do this by copying the numerator and denominator directly to the member object.*/
void myFraction::operator=(myFraction frac)
{
	numerator = frac.numerator;
	denominator = frac.denominator;
};

/*Overloading - operator - take in a myFraction object. Find a common denominator. Take 
member fraction - passed fraction. Return the result.*/
myFraction myFraction::operator-(myFraction frac)
{
	myFraction temp;
	if (denominator != frac.denominator)
	{
		myFraction temp1, temp2;
		temp1.numerator = frac.numerator * denominator;				//right hand
		temp1.denominator = frac.denominator * denominator;
		temp2.numerator = numerator * frac.denominator;				//left hand
		temp2.denominator = denominator * frac.denominator;
		temp.numerator = temp2.numerator - temp1.numerator;
		temp.denominator = temp1.denominator;
	}
	else
	{
		temp.numerator = numerator - frac.numerator;
		temp.denominator = denominator;
	}
	return temp;
};

/*overloading * operator, with object * object. Passed in is a myFraction. This is multiplied with
the member object. result saved to temp object. the temp object is then returned.*/
myFraction myFraction::operator*(myFraction frac)
{
	myFraction temp;
	temp.denominator = denominator * frac.denominator;
	temp.numerator = numerator * frac.numerator;
	return temp;
};

/*overloading * operator, with object * int. Passed in is an int. Because an integer in fraction
from is int/1, we just multiply numerator by int. save into temp object. copy over existing
denominator and return the temp object. */
myFraction myFraction::operator*(int number)
{
	myFraction temp;
	temp.denominator = denominator;
	temp.numerator = numerator * number;
	return temp;
};

/*overloading * operator, with int * object. Passed in is an int and myFraction. We create a temp
object. Then multiply myFraction's numerator by int. Save into temp numerator. copy myFraction denominator
into temp's denominator. Return temp. */
myFraction operator*(int number, myFraction frac)
{
	myFraction temp;
	temp.denominator = frac.denominator;
	temp.numerator = number * frac.numerator;
	return temp;
};

