/*
Chris Arnold
200276366	
Assignment #3, Question 1
Will Combine previously made classes to compare recursive and iterative solutions to the Fibonacci sequence
Timer header and cpp was taken from the lab material and is not mine! I will implement in the driver to show the timings.
*/
#include <iostream>
using namespace std;
#include "timer.h"
#include "iterativeFibonacci.h"
#include "recursiveFibonacci.h"
#include <iomanip>
/**/
int main()
{
	double recursiveTime, iterativeTime, difference = 0.0;			//declaring and initializing local variables to 0
	unsigned long long RecResult, ItResult;
	int value = 0;
	Timer theTimer;							//initializing the function timing class
	FibonacciRecursive Recursive;
	iterativeFibonacci Iterative;
	cout << "This program will compare the running times of iterative and recursive functions to solve a Fibonacci series. " << endl
		<< "---------------------------------------------------------------------------------------------" << endl
		<< "| nth value    | Iterative Time   | Recursive Time  | Difference   |      Fibonacci Value    |" << endl;

	for(int i = 0; i < 50; i++)
	{
		theTimer.start();
		ItResult = Iterative.findNthValue(value);
		theTimer.stop();
		iterativeTime = theTimer.getElapsedTime();		//finish calculating fibonacci value and the execution time
		
		theTimer.start();
		RecResult = Recursive.findNthNumber(value);
		theTimer.stop();
		recursiveTime = theTimer.getElapsedTime();		//finish calcuating fibonacci value and the execution time

		if(ItResult == RecResult) {}		//if for some reason the two programs do not calculate the same fibonacci value
		else
		{
			cout << "An Error has occured :(" << endl;
			return 1;
		}
		difference = recursiveTime - iterativeTime;
		
		//now will fill in table
		cout  << "|" << setw(14) << value << "|" << setw(18) << iterativeTime << "|" << setw(17) << recursiveTime << "|" 
			 << setw(14) << difference << "|" << setw(25) << ItResult << "|" << endl;
		value++;
	}

	return 0;
};
