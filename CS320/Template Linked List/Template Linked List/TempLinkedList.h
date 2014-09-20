#ifndef TEMPLINKEDLIST_H
#define TEMPLINKEDLIST_H
#include <iostream>
using namespace std;

template <class T>
class MyNode
{
private:
	T data;
public:
	MyNode *next;
	MyNode(T iData);
	MyNode(T iData, MyNode * point);
	template<class T> friend class LinkedList;
};


template <class T>
class LinkedList
{
private:
	MyNode<T> *head;
	int size;
public:
	LinkedList();
	void removeNode();		//removes element from the list. NOTE: only first occurance will be deleted. 
	void searchMyNode();	//searches list for an element. Outputs search results
	void addANode();		//adds an element to the list.
	void print();			//outputs the list to the screen.

};


#endif
void printMenu();			//user menu for valid operations. 
#include "TempLinkedList.cpp"