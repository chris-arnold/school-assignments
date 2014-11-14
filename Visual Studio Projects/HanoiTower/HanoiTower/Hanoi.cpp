#include "Hanoi.h"
#include <iostream>
#include <iomanip>

/*
in - size of the tower
initialize the 3 stacks to size, fill column a with disks
out - nothing
*/
HanoiTower::HanoiTower(int size)
{
	stack colA(size);
	stack colB(size);
	stack colC(size);
	towerSize = size;
	for(int i = 0; i < size; i++)
	{
		colA.add(size - i);
	}
}

/*
in - nothing
Solves the Tower of Hanoi
out - nothing
*/
void HanoiTower::solvePuzzle()
{

}


/*
in - nothing
prints out the game board to the user
out - nothing
*/
void HanoiTower::printGame()
{
	for(int i = towerSize; i > 0; i--)
	{
		cout << setw(towerSize) << colA.getElement(i)
			<< setw(towerSize) << colB.getElement(i)
			<< setw(towerSize) << colC.getElement(i)
			<< endl;
	}
	cout << setw((towerSize/2)) << 'A'
		<< setw(towerSize) << 'B'
		<< setw(towerSize) << 'C'
		<< endl;
}