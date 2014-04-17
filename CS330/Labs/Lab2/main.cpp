#include <iostream>
#include <cstring>
#include <fstream>
#include "oneline.h"

using namespace std;

int main()
{
	OneLine a;
ifstream inFile;
inFile.open("test.txt");


while(inFile)
{
	a.readLine(inFile);
	a.breakLine();
	if( a.returnLine() != "")		//if line read in is blank, don't reverse
	{
		cout << "Reversing the Words" << endl;
		a.printReverse();
		cout << "Done Reversing the Words" << endl << endl;
	}
}

inFile.close();

}
