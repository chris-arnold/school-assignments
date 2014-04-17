//NOTE:: 93 is the largest number that can be found using unsigned long long type


#include "iterativeFibonacci.h"
//in - nothing
//set all variables to 0
//out - nothing
iterativeFibonacci::iterativeFibonacci()
{
	current = previous1 = previous2 = 0;
};

/* 
in - int length -> the nth value to find
calculates the fibonacci value.
out - unsigned long long -> the nth fibonacci value
*/
unsigned long long iterativeFibonacci::findNthValue(int length)
{
	for(int i = 0; i <= length; i++)
	{
		if (i == 0)				//base case 1
		{
			current = previous1 = previous2 = 0;
		}
		else if (i == 1)		//base case 2
		{
			current = 1;
			previous1 = previous2 = 0;
		}
		else					//slide values, calculate new fibonacci.
		{
			previous2 = previous1;
			previous1 = current;
			current = previous2 + previous1;
		}
	}

	return current;
};