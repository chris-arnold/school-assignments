/*
CS 210, Assignment #2 October 13, 2011
Chris Arnold
200276366

Question #2 - creating a fraction class with specified overloaded operators.
*/

#include "fraction.h"


int main()
{

	myFraction F1, F2, Result;		//two user fractions and one to hold the results of calculations.
	int iNum, iDen, myInt;			//usage in order - inputed numerator - inputed denominator - integer to be multiplied with
	cout << "Enter the numerator for fraction 1: ";
	cin >> iNum;
	do{
	cout << "Enter the denominator for fraction 1: ";
	cin >> iDen;
	if(iDen == 0)
		cout << "Invalid input. Denominator cannot be 0" << endl;
	}while(iDen == 0);					//ensure the denominator is never 0
	F1.setFraction(iNum, iDen);

	//same as above but for second user fraction.
	cout << "Enter the numerator for fraction 2: ";
	cin >> iNum;
	do{
	cout << "Enter the denominator for fraction 2: ";
	cin >> iDen;
	if(iDen == 0)
		cout << "Invalid input. Denominator canot be 0" << endl;
	}while(iDen == 0);
	F2.setFraction(iNum, iDen);

	cout << "Please enter an integer to mulitply fractions by: ";
	cin >> myInt;
	
	//from here on out is testing. Output should be sufficient to understanding whats happening.
	cout << "Thank you for your input. Testing will commence shortly. Firstly " << endl
		<< "the contents of the fractions: " << endl
		<< "Fraction 1: "; F1.printFraction();
	cout << endl << "Fraction 2: "; F2.printFraction();
	cout << endl << endl;
	
	cout << "Fraction 1 + Fraction 2 = ";
	Result = F1 + F2;
	Result.printFraction(); cout << endl;
	
	cout << "Fraction 1 * Fraction 2 = ";
	Result = F1 * F2;
	Result.printFraction(); cout << endl;

	cout << "Fraction 1 * " << myInt << " = ";
	Result = F1 * myInt;
	Result.printFraction(); cout << endl;

	cout << myInt << " * Fraction 2 = ";
	Result = myInt * F2;
	Result.printFraction(); cout << endl;

	cout << "Fraction 1 - Fraction 2 = ";
	Result = F1 - F2;
	Result.printFraction(); cout << endl;

	cout << "Is Fraction 1 > Fraction 2? ";
	if (F1 > F2)
		cout << "YES!! " << endl;
	else
		cout << "NO :(" << endl;

	return 0;
}
