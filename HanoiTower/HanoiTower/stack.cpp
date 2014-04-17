#include "stack.h"
#include <iostream>


/*
in - nothing
Initialize stack top to -1 so when an item is added, the top is aligned with the index of array
array will be of max size
out - nothing
*/
stack::stack()
{
	top = -1;
}

/*
in - the stacks size
Initialize lesser cap on stack. Better for memory :)
out - nothing
*/
stack::stack(int size)
{
	top = -1;
	tower[size];
}

/*
in - the item to be added to the stack
Item is added to the top of the stack and the top is updated
out - nothing
*/
void stack::add(ItemType disk)
{
	top++;
	tower[top] = disk;
}

/*
in - nothing
Remove top value from the stack. Done by decreasing the top of the stack. We also set the old 
cell to NULL to 'delete' the data.
out - nothing
*/
void stack::remove()
{
	tower[top] = NULL;
	top--;
}

/*
in - nothing
if top == -1, stack is empty
out - boolean result of above equation.
*/
bool stack::isEmpty() const
{
	return(top == -1);
}

/*
in - nothing
out - value of top
*/
int stack::getTop() const
{
	return top;
}

int stack::getElement(int location) const
{
	return tower[location];
}