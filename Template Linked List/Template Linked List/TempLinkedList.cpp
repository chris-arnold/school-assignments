#ifndef TEMPLINKEDLIST_CPP
#define TEMPLINKEDLIST_CPP

#include "TempLinkedList.h"
/*All functions collect any necessary data from the user in order to operate.*/

/* Creates new linked list and assigns the head to NULL. Size starts at 0. */
template <class T>
LinkedList<T>::LinkedList()
{
	head = NULL;
	size = 0;
};

/* Asks the user what value they would like to remove. Then searches for that element. 
A special case exists for if the data in question is at the beginning of the list, otherwise
If the data is found it is deleted and the list is linked around it. Size of the list is also decremented.
If the value is not found in the list the user is notified before funcion exits. NOTE:  If a value exists 
more than once in the list, only the first occurance will be deleted.*/
template <class T>
void LinkedList<T>::removeNode()
{
	T delData;
	cout << "What value would you like to remove? ";
	cin >> delData;
	MyNode<T> * current, * previous;
	current = head;
	if(size == 0)				//if list is empty, nothing can be done..
	{
		cout << "The list is empty, therefore you cannot delete a value. " << endl;
		return;
	}

	if(current->data == delData)
	{
		head = current->next;
		delete current;
		size--;
		return;
	}
	previous = current;
	current = current->next;
	while(current != NULL)
	{
		if(current->data == delData)
		{
			previous->next = current->next;
			delete current;
			size--;
			return;
		}
		else
		{
			previous = current;
			current = current->next;
		}
	}
	cout << "The inputed element '" << delData << "' was not found in the list. " << endl;
};

/* Searches the list. Asks the user for the data to be searched for. User is then told if the data
exists anywhere within the list. */
template <class T>
void LinkedList<T>::searchMyNode()
{
	T findData;
	cout << "What value would you like to search for? ";
	cin >> findData;
	MyNode<T> * p;
	p = head;
	while(p != NULL)
	{
		if(p->data == findData)
		{
			cout << "Your data " << findData << " was found in the linked list!!" << endl;
			return;
		}
		else
		{
		p = p->next;
		}
	}
	cout << "Your data " << findData << " was NOT found in the list :(" << endl;
};

/* Adds an element to the list. This value is always added to the end of the list. Increments
the size of the list by 1.*/
template <class T>
void LinkedList<T>::addANode()
{
	T iData;
	cout << "Please enter a value to add to the list: ";
	cin >> iData;
	MyNode<T> *p;
	if(head == NULL)
	{
		head = new MyNode<T>(iData, NULL);
	}
	else
	{
		p = head;
		while(p->next != NULL)
		{
			p = p->next;
		}
		p->next = new MyNode<T>(iData, NULL);
	}
	size++;
};

/* Prints the list's data to the screen. */
template <class T>
void LinkedList<T>::print()
{
	MyNode<T> *p;
	p = head;
	while(p != NULL)
	{
		cout << p->data << endl;
		p = p->next;
	}
};


/* Takes in an element. Assigns that to the current location and creates a new NULL
element infront of it.*/
template <class T>
MyNode<T>::MyNode(T iData)
{
	data = iData;
	next = NULL;
};

/* Takes in a piece of data and a MyNode. assigns the piece of data to the current NULL location
and makes the next point the Node Passed in. */
template <class T>
MyNode<T>::MyNode(T iData, MyNode * point)
{
	data = iData;
	next = point;
};

#endif
