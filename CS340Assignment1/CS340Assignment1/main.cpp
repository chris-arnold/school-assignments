/* CS 340 Advanced Data Structures and Algorithm Design, Winter 2013
Assignment #1 - January 15, 2013
Question #4(a)
By: Chris Arnold

Code has been compiled and tested in Microsoft Visual Studio 2012, and G++ on Mac OSX 10.8.2

*/
#include <iostream>
#include <time.h>
#include <cmath>

using namespace std;

long long assignment1Algorithm(long long n);

int main()
{
	long long n, result;
	double calc;
	clock_t start, finish; 
	long double timeUsed;
	cout << "Insert the number n: ";
	cin >> n;
	cout << endl << "Input n is: " << n << endl;
	
	start = clock();
	result = assignment1Algorithm(n);
	finish = clock();
	timeUsed = ((long double)(finish - start))/CLOCKS_PER_SEC;
	timeUsed = timeUsed*1000000;

	cout << "TIME USED HAS BEEN MULTIPLIED BY 1,000,000" << endl;
	cout << "Result of Algorithm: " << result << endl;											//part i
	cout << "Value of n / result: " << (double)n/result << endl;								//part ii
	cout << "Value of n*log2(n) / result: " << (double)n*(log(n)/log(2))/result << endl;		//part iii
	cout << "Value of pow(n,1.5) / result: " << pow(n,1.5)/result << endl;						//part iv
	cout << "Value of timeUsed: " << timeUsed << endl;											//part v
	cout << "Value of n / timeUsed: " << (double)n/timeUsed << endl;							//part vi
	cout << "Value of n*log2(n) / timeUsed: " << (double)n*(log(n)/log(2))/timeUsed << endl;	//part vii
	cout << "Value of pow(n,1.5) / timeUsed: " << pow(n,1.5)/timeUsed << endl;					//part viii

	return 0;
}


long long assignment1Algorithm(long long n)
{
	long long sum = 0;

	for(long long i = 1; i <= n; i++)
	{
		for(long long j = n; j > 1; j = floor(j/2))
		{
			sum += 1;
		}
	}
	return(sum);
}