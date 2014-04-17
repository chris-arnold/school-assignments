#include<iostream>

using namespace std;

class LifeBoard
{
private:
	int col, row;
	bool world[10][10];
	bool changes[10][10];

public:
	LifeBoard();
	void checkLocations();		//checks and marks locations to be changed. after board is entirely checked, changes are made.
	void makePointTrue(int r, int c);
	void updateWorld();
	void print();
};