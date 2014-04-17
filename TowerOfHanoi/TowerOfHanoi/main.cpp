#include "Disks.h"
#include "HanoiTower.h"

#include <iostream>


int main()
{
	int aNumber;
	cout << "Tower Of Hanoi. Please enter how many disks to solve for: ";
	cin >> aNumber;

	HanoiTower Tower(aNumber);
	Tower.moveDiskStack();

	Tower.printField();

	return 0;
}