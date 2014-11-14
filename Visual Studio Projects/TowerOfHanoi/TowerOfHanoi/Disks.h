#ifndef DISKS_H
#define DISKS_H

using namespace std;
#include <iostream>
#include <iomanip>
class Disks
{
private:
	int size;
	int tier;				//tier is counted from the bottom up, the base of any stack is @ tier 1
	char previousPeg;		//peg the disk was on last
	char peg;				//pegs a, b, c are available

public:
	Disks();										//default constructor for use with dynamic array
	Disks(int size, int tier);						//initialize the size of the disk, its tier, and the peg of a to begin
	void changeInfo(int size, int tier);			//allows the size and tier values to be initialized inthe dynamic array
	void updateLocation(int iLevel, char iPeg);		//when disk is moved, its tier and current peg location must be updated.
	int getTier();									//returns the tier of the disk
	char getPeg();									//returns the current peg location of the disk
	char getPreviousPeg();							//returns the previous tier of the disk
	void printDisk();								//prints out the disk
};	

#endif