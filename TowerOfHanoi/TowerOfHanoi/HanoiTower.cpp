#include "HanoiTower.h"

using namespace std;

/*
Takes in the size of the tower.
Initializes tower elements(disks) to the correct tier and size.
Outputs nothing.
*/
HanoiTower::HanoiTower(int towerSize)
{
	heightA = heightB = heightC = 0;
	height = towerSize;
	initialHeight = towerSize;
	myTower = new Disks[height];
	for(int i = 0; i < height; i++)
	{
		myTower[i].changeInfo((towerSize), (i + 1));		//myTower[0] = largest disk(towerSize); myTower[towerSize] contains smallest disk(size 1)
		towerSize--;
		heightA++;
	}
};

/*
in - nothing
move the entire stack from peg a to peg c
out - nothig.
*/
void HanoiTower::moveDiskStack()
{
	int evenOrOdd = height % 2;
	switch (evenOrOdd)
	{
		case 0:					//height mod 2 is zero == even number
			{
				myTower[height].updateLocation(1, 'b');
				heightA--;
				heightB++;
				break;
			}
		case 1:					//is odd height
			{
				myTower[height].updateLocation(1, 'c');
				heightC++;
				heightA--;
				break;
			}
		default:				//something went horribly wrong if the height is neither even nor odd..
			{
				cout << "There is a T-rex at your window, who looks mighty hungry right now :) " << endl;
				return;
				break;
			}
	}
	height--;
	//above is determining the first move, which depends on the initial size of the stack.
	//now it should be relatively straight forward for solving. 


};

/**/
void HanoiTower::moveSubStack(char iPeg)		//iPeg contains the location of the sub stack to be moved.
{
	if(heightB == 0)
	{
		heightC++;
		myTower[height - 1].updateLocation(heightC, 'c');
		heightA--;
		height--;
		moveSubStack('c');
	}
	else if(heightC == 0)
	{
		heightB++;
		myTower[height - 1].updateLocation(heightB, 'b');
		heightA--;
		height--;
		moveSubStack('b');
	}


	/*
	/move height-1 to empty
		/move 1 onto height-1

		move height-2 to empty
		/do about

		move height-3 to empty 
		/do above
		*/
};

/*
in - a peg
out - the height of that peg
*/
int HanoiTower::getHeightPeg(char thePeg)
{
	if(thePeg == 'a')
		return heightA;
	else if(thePeg == 'b')
		return heightB;
	else if(thePeg == 'c')
		return heightC;
	else
		return -1;
};

/*
Input - nothing
Start at highest tier possible(height)
Search for any disks at that level.
	If found get the current peg and output the disk in correct location
After array is searched, move on to next lowest tier until tier 1 has been checked.

Then output the pegs
Output - puzzle to user
*/
void HanoiTower::printField()
{
	int currentTier;
	int height = initialHeight;
	char currentPeg;
	for(int i = height; i > 0; i--)		
	{
		for(int j = 0; j < height; j++)
		{
			currentTier = myTower[j].getTier();
			if(currentTier == height)
			{
				myTower[j].printDisk();
			}
		}
		cout << endl;
	}

	for(int k = 0; k < 3; k++)
	{
		for(int i = 0; i < height; i++)
		{
			if(i == (height / 2))
				cout << "|";
			else
				cout << "_";
		}

		cout << "  ";
	}
	cout << endl;

	cout << setw(height/2) << "A" << setw(height) << "B" << setw(height) << "C" << endl << endl;
};