#ifndef BSTREE_CPP
#define BSTREE_CPP

#include "BSTree.h"
#include <iostream>
using namespace std;

template <class Type>
Node<Type>::Node(Type item, Node *Pright, Node *Pleft)
{
	data = item;
	right = Pright;
	left = Pleft;
};

template <class Type>
BSTree<Type>::BSTree()
{
	root = NULL;
};

template <class Type>
void Node<Type>::add(Type item, Node *&p)
{
	if(p == 0)		//empty leaf found. Add value
	{
		p = new Node(item, NULL, NULL);
	}
	else if(item < p->data)		//item is less than current node. needs to go to left hand side
	{
		add(item, p->left);
	}
	else if(item > p->data)		//item is greater than current node. needs to go on right side
	{
		add(item, p->right);
	}
	else
	{
		//p->data = item;
	}
};

template <class Type>
void BSTree<Type>::insert(Type item)
{
	root->add(item, root);
};


template <class Type>
bool BSTree<Type>::search(Type item)
{
	if(root->search(item) == NULL)
		return false;
	else
		return true;
};

template <class Type>
void BSTree<Type>::remove(Type item)
{
	root->remove(item, root);
};

template <class Type>
void Node<Type>::remove(Type item, Node *&p)
{
	Node *deletedp;
	if(item == this->data)			//item to be deleted is found	//search function modified to delete on find.
	{
		deletedp = p;
		if(p->left == 0)
		{
			p = p->right;
			delete deletedp;
		}
		else if(p->right == 0)
		{
			p = p->left;
			delete deletedp;
		}
		else
		{
			Node *temp;
			temp = p->left;
			while(temp->right)
			{
				temp = temp->right;
			}
			p->data = temp->data;
			remove(temp->data, p->left);
		}
		return;
	}
	else if(item < this->data)			//item to delete is less than current item.
	{
		if(left == NULL)		//item not in tree
		{
			return;
		}
		else
		{
			return left->remove(item, left);
		}
	}
	else if(item > this->data)			//item to delete is greater than current item.
	{
		if(right == NULL)			//item not in tree
		{
			return;
		}
		else
		{
			return right->remove(item, right);
		}
	}
	else
	{
		cout << "Something I did not think of has occured in the Node search function. " << endl;
		return;
	}
};

template <class Type>
bool Node<Type>::search(Type item)
{
	if(item == this->data)
		return true;
	else if(item < this->data)
	{
		if(left == NULL)		//item not in tree
		{
			return false;
		}
		else
			return left->search(item);
	}
	else if(item > this->data)
	{
		if(right == NULL)			//item not in tree
		{
			return false;
		}
		else
			return right->search(item);
	}
	else
	{
		cout << "Something I did not think of has occured in the Node search function. " << endl;
		return false;
	}
};



template <class Type>
void BSTree<Type>::printTree()
{
	root->print(root);
	cout << endl;
};

template <class Type>
void BSTree<Type>::printPost()
{
	root->Post(root);
	cout << endl;
};

template <class Type>
void Node<Type>::Post(Node *temp)
{
	if(temp != 0)
	{
		Post(temp->left);
		Post(temp->right);
		cout << temp->data << " ";
	}
};

template <class Type>
void BSTree<Type>::printPre()
{
	root->Pre(root);
	cout << endl;
};

template <class Type>
void Node<Type>::Pre(Node *temp)
{
	if(temp != 0)
	{
		cout << temp->data << " ";
		Pre(temp->left);
		Pre(temp->right);
	};
};

template <class Type>
void Node<Type>::print(Node *temp)
{
	if(temp != 0)
	{
		print(temp->left);
		cout << temp->data << " ";
		print(temp->right);
	}
};

#endif