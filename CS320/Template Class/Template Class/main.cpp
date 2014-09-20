//Testing a template class 


#include "myclass.h"


int main()
{
	myClass<int> C1;
	myClass<char> C2;
	int myLength;
	cout << "Enter a length: ";
	cin >> myLength;
	C1.setData(myLength);
	cout << "Enter Chars: ";
	C2.setData(myLength);

	cout << "C1 - int class print out: " << endl;
	C1.printData();
	cout << "C2 - char class print out: " << endl;
	C2.printData();

	return 0;
};