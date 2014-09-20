#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
using namespace std;

template<class T>
class queue
{
protected:
	class Node
	{
	public:
		T data;
		Node *next;

		Node();
		Node(T info);
	};

	Node *front, *back;
	int length;
public:
	queue();
	void enqueue(T info);		//PRE Init queue passes in data. POST - passed data is at the end of the queue
	void dequeue();				//PRE init queue. POST - If available, item will be removed from the beginning of the queue
	bool empty();				//PRE init queue. POST - returns true if queue is empty. else false
	int getSize();				//PRE init queue. POST - returns size of the queue.
	T getFrontData();				//PRE init queue. POST - returns item at front of queue
	void print();
};

#endif
#include "queue.cpp"