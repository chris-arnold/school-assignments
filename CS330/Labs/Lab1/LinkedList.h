// LinkedList.h

#if !defined __LINKEDLIST_H__
#define __LINKEDLIST_H__
#include <cstdlib>
#include <iostream>
using namespace std;



class LinkedList;

class ListElement
{
public:    
	int datum;
    ListElement* next;
    

    ListElement (int const&, ListElement*);
    
	int const& Datum () const;
    ListElement const* Next () const;

    friend class LinkedList;
};


class LinkedList
{
    ListElement* head;
    ListElement* tail;
public:
    LinkedList ();
    ~LinkedList ();

    LinkedList (LinkedList const&);
    LinkedList& operator = (LinkedList const&);

    ListElement const* Head () const;
    ListElement const* Tail () const;
    bool IsEmpty () const;
    int const& First () const;
    int const& Last () const;

    void Prepend (int const&);
    void Append (int const&);
    void Purge ();
    void InsertAfter (ListElement const*, int const&);
    void InsertBefore (ListElement const*, int const&);

	void Insert (int const&);
    
	void Delete(int const&);
    void Print();

};

#endif
