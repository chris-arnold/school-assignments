#include <iostream>

using namespace std;

class iterativeFibonacci
{
private:
	unsigned long long current, previous1, previous2;		//long long ints used to have a cap of about the 93rd Fibonacci value
															//values will hold the current nTh value, and the previous two needed to calculate fibonacci values
public:
	iterativeFibonacci();			//initialize all values to zero
	unsigned long long findNthValue(int length);		//calculate fibonacci value length, and return it.

};