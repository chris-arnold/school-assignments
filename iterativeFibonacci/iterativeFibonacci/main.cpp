#include "iterativeFibonacci.h"


int main()
{
	iterativeFibonacci num1;
	int number;
	unsigned long long thatnumber;
	char wtd;
	do{
	cout << "Please enter the Nth number of Fibonacci series you'd like to find (Max 93): ";
	cin >> number;
	thatnumber = num1.findNthValue(number);
	cout << "The " << number << " number in the series is: "<< thatnumber << ". " << endl;
	cout << "Continue(y/n)? ";
	cin >> wtd;
	}while(wtd != 'n');				//continues to query for values to find until 'n' is inputed
};