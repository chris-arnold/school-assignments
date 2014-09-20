#include "stack.h"
#include <string>
int main()
{
	stack s1;
	string infix;
	int length;
	char currentitem;
	bool done = false;
	cout << "Welcome! " << endl << "This program will convert infix notation to postfix notation. " << endl
		<< "Please type your infix equation and them press enter to be amazed! " << endl;
	getline(cin, infix);
	length = infix.length();
	for(int i = 0; i < length; i++)
	{
		currentitem = infix[i];			//grab the character from input to process.
		done = false;
		switch(currentitem)
		{
		case '(':
			s1.push(currentitem);
			break;
		case ')':
			while(s1.getTop() != '(')
			{
				cout << s1.getTop();
				s1.pop();
			}
			s1.pop();
			break;
		case '*':
		case '/':
		case '^':									//all three of these operators have the same precednece and all require two operands so can be treated the same.
			while(s1.getTop() != '(')
			{
				if(s1.isEmpty())					//empty stack gets operator
				{
					s1.push(currentitem);
					done = true;
					break;
				}
				else if(s1.getTop() == '+' || s1.getTop() == '-' || s1.getTop() == '(')		//any of these items must be dealt with before the current operator
				{
					break;
				}
				else
				{
					cout << s1.getTop();
					s1.pop();
				}
			}
			if(!done)							//reason is same as below, to fix a double push on empty stack
				s1.push(currentitem);
			break;
		case '+':
		case '-':
			while(s1.getTop() != '(')					
			{
				if(s1.isEmpty())					//if stack is empty, push item onto stack
				{
					s1.push(currentitem);
					done = true;					//here because the break doesn't exit the case for some reason and causes a double push :|
					break;
				}
				else								//otherwise, empty the stack item by item.
				{
					cout << s1.getTop();
					s1.pop();
					break;
				}
			}
			if(!done)								//this fixes my double push on empty stack problem
				s1.push(currentitem);
			break;
		default:									//if not an operator, output as postfix.
			cout << currentitem;
		}
	}
	while(!s1.isEmpty())		//after all items read from input, we clear out the stack.
	{
		cout << s1.getTop();
		s1.pop();
	}
	cout << endl;
	return 0;
};