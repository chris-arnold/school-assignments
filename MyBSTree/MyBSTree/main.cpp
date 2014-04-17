#include "BSTree.h"
#include <iostream>
using namespace std;


int main()
{
	BSTree<int> tree;
	int value;
	char wtd;
	do
	{
		cout << "What would you like to do? Insert (i), print(p), delete(d), search(s), quit(q): ";
		cin >> wtd;
		switch (wtd)
		{
		case 'i':
			cout << "Enter a number: ";
			cin >> value;
			tree.insert(value);
			break;
		case 'p':
			cout << "Printing the tree in order: " << endl;
			tree.printTree();
			cout << endl << endl << "Printing the tree in Post Order: " << endl;
			tree.printPost();
			cout << endl << endl << "Printing the tree in Pre Order: " << endl;
			tree.printPre();
			cout << endl;
			break;
		case 'd':
			cout << "Enter a value to delete: ";
			cin >> value;
			tree.remove(value);
			break;
		case 's':
			cout << "Enter a value to search for: ";
			cin >> value;
			if(tree.search(value))
				cout << "The item " << value << " was found in the tree. " << endl;
			else
				cout << "The item " << value << " was not found in the tree. " << endl;
			break;
		default:
			cout << "Invalid input was recieved. Try again. " << endl;
			break;
		}

	}while(wtd != 'q');

	cout << "Printing the tree in order: " << endl;
	tree.printTree();
	cout << endl << endl << "Printing the tree in Post Order: " << endl;
	tree.printPost();
	cout << endl << endl << "Printing the tree in Pre Order: " << endl;
	tree.printPre();
	cout << endl;
	return 0;
};