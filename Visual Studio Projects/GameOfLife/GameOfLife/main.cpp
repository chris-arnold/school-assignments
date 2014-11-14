#include "Life.h"

int main()
{
	LifeBoard l1;

	//cout << "This is a simple test of the life game board: " << endl;
	l1.makePointTrue(5, 5);
	l1.makePointTrue(5, 6);
	l1.makePointTrue(6, 5);
	l1.makePointTrue(7, 8);
	l1.makePointTrue(8, 7);
	l1.makePointTrue(8, 8);
	while(1)
	{
		l1.checkLocations();
		l1.updateWorld();
		l1.print();
		system("PAUSE");
	}
	return 0;
};