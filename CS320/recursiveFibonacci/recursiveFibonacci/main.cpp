#include "recursiveFibonacci.h"


int main()
{
	FibonacciRecursive num1;
	int number;
	unsigned long long thatnumber;
	char wtd;
	do{
	cout << "Please enter the Nth number of Fibonacci series you'd like to find: ";
	cin >> number;
	thatnumber = num1.findNthNumber(number);
	cout << "The " << number << " number in the series is: "<< thatnumber << ". " << endl;
	cout << "Continue(y/n)? ";
	cin >> wtd;
	}while(wtd != 'n');				//continues to query for values to find until 'n' is inputed
};
