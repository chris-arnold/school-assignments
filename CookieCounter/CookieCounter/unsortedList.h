#ifndef UNSORTEDLIST_H
#define UNSORTEDLIST_H

#include "Definitions.h"

class unsortedList
{
private:
	int length;
	Type List[MAXSIZE];

public:
	unsortedList();			//pre - uninitialized variables -- post - array init to 0's, length set to 0
	bool isFull() const;	//pre - an initialized list -- post - returns if list is full
	bool isEmpty() const;	//pre - init list -- post - returns if list is empty
	int lengthIs() const;	//pre - an initialized list -- post - returns length of list
	void retrieveItem(Type& item, bool& found);		//pre - an initalized list(takes in item looking for, bool value to flag if found -- post - if item is found, bool-found is true, item = item found
	void insertItem(Type item);		//pre - an initialized list -- post - item has been added to the list if list not full
	void deleteItem(Type item);		//pre - init. list -- post - searches for item. if found it is deleted.
	void resetList();		//pre - init list -- post - list full of 0's, length = 0
	Type getItem(int index);	//pre - init list -- post - returns list element @ provided index

};

#endif