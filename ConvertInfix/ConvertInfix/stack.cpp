#include "stack.h"

using namespace std;

stack::stack()
{
	top = -1;
};

void stack::pop()
{
	if(isEmpty())
	{
		return;
	}
	else
		top--;
};

void stack::push(Type item)
{
	if(isFull())
	{
			return;
	}
	else
	{
		top++;
		data[top] = item;
		return;
	}
};

Type stack::getTop()
{
	if(isEmpty())
	{
		return -1;
	}
	else
	{
		return data[top];
	}
};

bool stack::isFull()
{
	if(top == MAXSIZE)
		return true;
	else
		return false;

};

bool stack::isEmpty()
{
	if(top == -1)
		return true;
	else
		return false;
};