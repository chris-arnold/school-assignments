#include "recursiveFibonacci.h"

/*
in - int length -> the nth number to be found
Calculate the nth value using recursion.
out - unsigned long long -> the nth number in the series
*/
unsigned long long FibonacciRecursive::findNthNumber(int length)
{
	if(length == 1)
		return 1;
	else if(length == 0)
		return 0;			//base cases, otherwise return the function call.
	else
		return (findNthNumber(length-1) + findNthNumber(length-2));
};