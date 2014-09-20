#ifndef BSTREE_H
#define BSTREE_H
#include <iostream>
using namespace std;

template<class Type>
class BSTree;

template <class Type>
class Node
{
private:
	Type data;
	Node *left;
	Node *right;
public:
	Node(Type item, Node *Pright, Node *Pleft);	//Pre - init tree. POST - node is created with proper parent
	void add(Type item, Node *&p);		//recursive insert helper. PRE - init tree. POST - place is found for the item to be added into the tree.
	bool search(Type item);				//Recusrive helper function. PRE - init tree. POST -  Returns if the value is found in the tree
	void remove(Type item, Node *&p);	//Recursive remove function. PRE - init tree. POST - item passed in is removed from the tree if found.
	void print(Node *temp);				//Recursive in-order print function. PRE - init tree. POST - After all recursion is done, tree is printed in order to the screen
	void Post(Node *temp);				//Recursive post-order print function. PRE - init tree. POST - After all recursion is done, tree is printed in post order to the screen
	void Pre(Node *temp);				//Recursive pre-order print function. PRE - init tree. POST - After all recursion is done, tree is printed in pre order to the screen
	friend class BSTree<Type>;

};


template <class Type>
class BSTree
{
private:
	Node<Type> *root;
public:
	BSTree();					//PRE - Nothing. POST - root is null. 
	void insert(Type item);		//PRE - init Tree. POST - item is inserted into appropriate place in tree
	void remove(Type item);		//PRE - init Tree. POST - item is removed from the tree.
	void printTree();			//PRE - init Tree. POST - contents of the tree are printed to the user
	bool search(Type item);		//PRE - init Tree. POST - searches the tree for an item T/F returned.
	void printPost();			//PRE - init Tree. POST - Prints the tree Post Order to the screen
	void printPre();			//PRE - init Tree. POST - Prints the tree Pre Order to the screen

};
#endif

#include "BSTree.cpp"