#ifndef STACK_H
#define STACK_H
#include <iostream>

using namespace std;

typedef char Type;				//type of item the stack is taking.
const int MAXSIZE = 25;			//max size of the stack


class stack
{
private:
	Type data[MAXSIZE];		//holds the data in the stack.
	int top;				//tracks the top of the stack

public:
	stack();				//PRE - nothing. POST - initilized stack
	void pop();				//PRE - init. stack. POST - top item is removed. if empty, nothing is done.
	void push(Type item);	//PRE - init. stack. POST - item is added to top of stack as long as stack isn't full
	Type getTop();			//PRE - init. stack. POST - item at top is returned
	bool isFull();			//PRE - init. stack. POST - returns if stack is full
	bool isEmpty();			//PRE - init. stack. POST - returns if stack is empty

};

#endif