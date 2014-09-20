#include "Life.h"
/*
class LifeBoard

	bool world[100][100];
	bool changes[100][100];
*/

LifeBoard::LifeBoard()
{
	col = 10;
	row = 10;
	for(int i = 0; i < row; i++)
	{
		for(int j = 0; j < col; j++)
		{
			world[i][j] = false;
			changes[i][j] = false;
		}
	}
};

void LifeBoard::makePointTrue(int r, int c)
{
	if(r < row && c < col && r >= 0 && c >= 0)
	{
		world[r][c] = true;
	}
	else
		cout << "That point is not on the game board. " << endl;

};

//checks and marks locations to be changed. after board is entirely checked, changes are made.
void LifeBoard::checkLocations()
{
	//set changes to current state
	for(int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			changes[i][j] = world[i][j];
		}
	}
	int counter = 0;
	for(int i =0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
				//run threw all locations in the world and check what the change will be.
		
			
				if(i == 0 && j == 0)		//special cases of corners(top left)
				{
					counter = 0;
					if(world[i+1][j])
						counter++;
					if(world[i+1][j+1])
						counter++;
					if(world[i][j+1])
						counter++;
				}
				else if(i == row && j == 0)		//case of bottom left corner
				{
					counter = 0;
					if(world[i-1][j])
						counter++;
					if(world[i-1][j+1])
						counter++;
					if(world[i][j+1])
						counter++;
				}
				else if(i == 0 && j == col)		//case of top right corner
				{
					counter = 0;
					if(world[i][j-1])
						counter++;
					if(world[i+1][j-1])
						counter++;
					if(world[i+1][j])
						counter++;
				}
				else if(i == row && j == col)	//case of bottom right corner
				{
					counter = 0;
					if(world[i][j-1])
						counter++;
					if(world[i-1][j-1])
						counter++;
					if(world[i-1][j])
						counter++;
				}
				else
				{
					if(i == 0)					//special case of top border
					{
						counter = 0;
						if(world[i][j-1])
							counter++;
						if(world[i+1][j-1])
							counter++;
						if(world[i+1][j])
							counter++;
						if(world[i+1][j+1])
							counter++;
						if(world[i][j+1])
							counter++;
					}
					else if(i == row)			//special case of bottom border
					{
						counter = 0;
						if(world[i][j-1])
							counter++;
						if(world[i-1][j-1])
							counter++;
						if(world[i-1][j])
							counter++;
						if(world[i-1][j+1])
							counter++;
						if(world[i][j+1])
							counter++;
					}
					else if(j == 0)				//special case left wall
					{
						counter = 0;
						if(world[i+1][j])
							counter++;
						if(world[i-1][j])
							counter++;
						if(world[i+1][j+1])
							counter++;
						if(world[i][j+1])
							counter++;
						if(world[i-1][j+1])
							counter++;
					}
					else if(j == col)			//special case, right wall
					{
						counter = 0;
						if(world[i+1][j])
							counter++;
						if(world[i-1][j])
							counter++;
						if(world[i+1][j-1])
							counter++;
						if(world[i][j-1])
							counter++;
						if(world[i-1][j-1])
							counter++;
					}
					else		 //any non exterior cell 
					{
						counter = 0;
						if(world[i-1][j-1])
							counter++;
						if(world[i][j-1])
							counter++;
						if(world[i+1][j-1])
							counter++;
						if(world[i-1][j])
							counter++;
						if(world[i+1][j])
							counter++;
						if(world[i-1][j+1])
							counter++;
						if(world[i][j+1])
							counter++;
						if(world[i+1][j+1])
							counter++;
					}
				}
			if(world[i][j])
			{
				if(counter == 2 || counter == 3)
					changes[i][j] = true;
			}
			else if(!world[i][j])
			{
				if(counter == 3)
					changes[i][j] = true;
			}
			else
			{
				changes[i][j] = false;
			}
			
		}

	}

};		

void LifeBoard::updateWorld()
{
	//copy changes to world
	for(int i = 0; i < row; i++)
	{
		for(int j = 0; j < col; j++)
		{
			world[i][j] = changes[i][j];
		}
	}
	
};
void LifeBoard::print()
{
	for (int i = 0; i < row; i++)
	{
		for(int j = 0; j < col; j++)
		{
			if(world[i][j])
			{
				cout << "+ ";
			}
			else
				cout << "  ";
		}
		cout << endl;
	}
	cout << endl;
};
