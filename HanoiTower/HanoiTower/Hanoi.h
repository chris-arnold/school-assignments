#include "stack.h"
#include <iostream>

class HanoiTower
{
private:
	stack colA;			// a stack for each column. Elements will remain sorted
	stack colB;			// should be relatively easy to implement and understand
	stack colC;
	int towerSize;
public:
	HanoiTower(int size);	//constructor that specifies the towers size
	void solvePuzzle();		//will solve the Tower of Hanoi
	void printGame();		//prints out the entire game board
};