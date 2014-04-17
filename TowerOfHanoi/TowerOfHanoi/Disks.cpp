#include "Disks.h"

using namespace std;

/*
Takes in a size and tier value. These are written to the disks size and tier. 
Peg is initialized as 'a'. The stack always starts on peg a. Previous peg is 
undefined at this point, so assigned a NULL value
*/
Disks::Disks(int iSize, int iTier)
{
	peg = 'a';
	size = iSize;
	tier = iTier;
	previousPeg = NULL;
};

/*
Takes nothing in, Sends nothing out. Initilaizes the size to 1, tier to 1, peg to a and previous peg to NULL
*/
Disks::Disks()
{
	size = 1;
	tier = 1;
	previousPeg = NULL;
	peg = 'a';
};

/*
Takes in the size and tier of the disk. Sets these values and outputs nothing. The peg is untouched as the default 
constructor already initialized it to 'a'
*/
void Disks::changeInfo(int iSize, int iTier)
{
	size = iSize;
	tier = iTier;
};

/*
Takes in the tier and peg location of the peg.
These values are then updated in the peg, also, the previousPeg is updated.
*/
void Disks::updateLocation(int level, char iPeg)
{
	tier = level;
	previousPeg = peg;
	peg = iPeg;
};

/*
Nothing comes in, the tier of the disk is returned.
*/
int Disks::getTier()
{
	return tier;
};

/*
Nothing comes in, the peg the disk is on is returned.
*/
char Disks::getPeg()
{
	return peg;
};

/*
Nothing comes in, the previous peg location of the disk is returned.
*/
char Disks::getPreviousPeg()
{
	return previousPeg;
};

/*
Nothing comes in, the disk is printed to the screen.
*/
void Disks::printDisk()		//add code to print the disks into appropriate columns for a, b, b, each being of width size
{
	cout << size;		//only for testing phase. after program works, change to a better output.
};