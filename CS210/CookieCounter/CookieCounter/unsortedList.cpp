#include "unsortedList.h"

unsortedList::unsortedList()
{
	length = 0;
	for(int i = 0; i < MAXSIZE; i++)
		List[i] = 0;
};

bool unsortedList::isFull() const
{
	return (length >= MAXSIZE);
};

bool unsortedList::isEmpty() const
{
	return (length == 0);
};

int unsortedList::lengthIs() const
{
	return length;
};

void unsortedList::retrieveItem(Type& item, bool& found)
{
	found = false;
	if(isEmpty())		//if empty, no need to search for item.
		return;
	for(int i = 0; i < length; i++)
	{
		if(List[i] == item)
		{
			found = true;			//mark as found
			item = List[i];			//update item
			return;					//exit function.
		}
	}
};

void unsortedList::insertItem(Type item)
{
	if(isFull())
	{
		cerr << "List is full. Could not write element " << item << " into list. Write failed. " << endl;
		return;
	}
	List[length] = item;
	length++;
};

void unsortedList::deleteItem(Type item)
{
	if(isEmpty())		//no need to search empty list
	{
		cout << "Item was not found, thus not deleted." << endl;
		return;
	}
	for(int i = 0; i < length; i++)
	{
		if(List[i] == item)
		{
			List[i] = List[length-1];			//overwrite to be deleted item with last item in list.
			List[length-1] = NULL;
			length--;						//decrease size by 1
			cout << "Item was successfully deleted. " << endl;
			return;							//exit function
		}
	}
	cout << "Item was not found, nor was it deleted. " << endl;
};

void unsortedList::resetList()
{
	for(int i = 0; i < length; i++)
		List[i] = 0;						//zero out list.
	length = 0;								//reset length to 0
};

Type unsortedList::getItem(int index)
{
	if(index <= MAXSIZE)				
		return List[index];
	else
	{
		cerr << "The item at the requested index could not be identified as a valid value. The value -1 will be returned. "
			<< endl << "Invalid index was: " << index << ". The length at this point in time was " << length << endl;
		return -1;
	}
};