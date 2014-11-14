#include <iostream>

using namespace std;
#include "ItemType.h"

class stack
{
private:
	ItemType tower[MaxItems];			//array to hold the stack information
	int top;							//height of the stack
public:
	stack();							//initialize the stack
	stack(int size);					//constructor to initialize to specific stack size
	bool isEmpty() const;				//return if the stack is empty or not
	void add(ItemType disk);			//add an item onto the top of the stack
	void remove();						//delete the item on the top of the stack
	int getTop() const;
	int getElement(int location) const;
}