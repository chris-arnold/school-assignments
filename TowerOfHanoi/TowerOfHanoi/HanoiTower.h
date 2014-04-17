#ifndef HANOITOWER_H
#define HANOITOWER_H	
using namespace std;
#include <iostream>
#include "Disks.h"

class HanoiTower
{
private:
	Disks *myTower;
	int height, initialHeight;
	int heightA, heightB, heightC;		//heights of towers on given peg
public:
	HanoiTower(int towerSize);		//initializes array of disks. each disk gets appropriate size, and location variables.
	void moveDiskStack();			//takes care of the logic required to move the tower from peg a to peg c.
	void moveSubStack(char iPeg);	//will move the intermediate smaller stacks around. iPeg is location of substack
	void printField();				//prints all disks current locations and the pegs.
	int getHeightPeg(char thePeg);
};

#endif