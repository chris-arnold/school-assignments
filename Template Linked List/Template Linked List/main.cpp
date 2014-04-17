/*
CS 210 Assignment #2, Question 1
Chris Arnold
200276366

Create a templated linked list.
This program creates a templated linked list which can do the following:
1) Add a Value to the linked list
2) Remove a value from the linked list
3) Search for a value in the linked list
4) Print the linked list
5) Add multiple values to the list at once

The main program also contains a menu for the user. 

*/

#include "TempLinkedList.h"

int main()
{
	LinkedList<float> l1;			//creates our linked list <char> makes it a list of characters. Can be any valid data type
	char wtd;						// what the user wants to do
	cout << "Welcome to the Templated Linked List! " << endl;
	printMenu();
	cout << "What would you like to do? ";
	cin >> wtd;
	while(wtd != 'q')			//continue to query the user until 'q' or quit is selected.
	{
		switch (wtd)			
		{
			case 'a':
				l1.addANode();
				break;
			case 'r':
				l1.removeNode();
				break;
			case 's':
				l1.searchMyNode();
				break;
			case 'p':
				l1.print();
				break;
			case 'm':
				printMenu();
				break;
			case 'i':
				int temp;
				cout << "How many values would you like to add? ";
				cin >> temp;
				for(int i = 0; i < temp; i++)
				{
					l1.addANode();
				}
				break;
			default:
				cout << "Invalid input. Try again. " << endl;
				break;
		}
		cout << "What would you like to do? ";
		cin >> wtd;
	}

	return 0;
};



void printMenu()
{
	cout << "---------------MENU---------------" << endl
		<< "----------------------------------" << endl
	  	<< "Add value ...................-> a" << endl
		<< "Remove Value ................-> r" << endl
		<< "Search for value ............-> s" << endl
		<< "Print out list ..............-> p" << endl
		<< "Print out this menu .........-> m" << endl
		<< "To quit .....................-> q" << endl
		<< "To input more than 1 value ..-> i" << endl;
};


