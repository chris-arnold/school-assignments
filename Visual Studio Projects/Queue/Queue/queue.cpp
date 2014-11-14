#ifndef QUEUE_CPP
#define	QUEUE_CPP

#include "queue.h"
#include <iostream>
using namespace std;

template<class T>
queue<T>::Node::Node(T info)
{
	data = info;
	next = NULL;
};

template<class T>
queue<T>::Node::Node()
{
	data = NULL;
	next = NULL;
};

template<class T>
queue<T>::queue()
{
	length = 0;
	front = NULL;
	back = NULL;
};

template<class T>
int queue<T>::getSize()
{
	return length;
};

template<class T>
bool queue<T>::empty()
{
	if(length == 0)
		return true;
	else
		return false;
};

template<class T>
void queue<T>::enqueue(T info)
{
	Node *temp = new Node(info);			//create the new node
	if(empty())							//if empty queue, new node is front and rear
	{
		front = back = temp;
	}
	else					//else, point current rear to temp. Make new rear(almost temp) = temp
	{
		back->next = temp;
		back = temp;
	}
	length++;
};

template<class T>
void queue<T>::dequeue()
{
	if(empty())
	{
		cout << "Queue is empty. Nothing could be removed. " << endl;
		return;
	}
	else
	{
		Node *p;
		p = front;
		front = front->next;
		if (front == NULL)
			back = NULL;
		delete p;
		length--;
	}
};

template<class T>
void queue<T>::print()
{
	if(empty())
	{
		cout << "Queue is empty. " << endl;
		return;
	}
	else
	{
		Node *p;
		p = front;
		for(int i = 0; i < length; i++)
		{
			cout << p->data << " ";
			p = p->next;
		}
		cout << endl;
	}
};

template<class T>
T queue<T>::getFrontData()
{
	return front->data;
};
#endif