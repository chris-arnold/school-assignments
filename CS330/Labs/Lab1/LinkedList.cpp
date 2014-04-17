//LinkedList.cpp

// Note: This implementation of LinkedList is based on 
// Chapter 4 of Bruno R. Preiss's Textbook: 
// "Data Structures and Algorithms with Object-Oriented Design Patterns
//    in C++"

#include <cstdlib>
#include <cassert>
#include "LinkedList.h"
using namespace std;

ListElement::ListElement(int const& _datum, ListElement * _next):
    datum (_datum), next (_next)
    {}


int const& ListElement::Datum () const
    { return datum; }


ListElement const* ListElement::Next () const
    { return next; }



LinkedList::LinkedList () :
    head (0),
    tail (0)
    {}


void LinkedList::Purge ()
{
    while (head != 0)
    {
        ListElement * const tmp = head;
        head = head->next;
        delete tmp;
    }
    tail = 0;
}

LinkedList::~LinkedList ()
{
	Purge();
}


ListElement const* LinkedList::Head () const
    { return head; }


ListElement const* LinkedList::Tail () const
    { return tail; }


bool LinkedList::IsEmpty () const
    { return head == 0; }


int const& LinkedList::First () const
{
    if (head == 0)
	{
		cout << "List is empty." << endl;
		exit(-1);	// Exit program with return code -1
	}
        
    return head->datum;
}

int const& LinkedList::Last () const
{
    if (tail == 0)
    {
		cout << "Error! " << endl;
		exit(-1);	// Exit program with return code -1
	}
    return tail->datum;
}


void LinkedList::Prepend (int const& item)
{
    ListElement * const tmp = new ListElement (item, head);
    if (head == 0)
                tail = tmp;
    head = tmp;
}


void LinkedList::Append (int const& item)
{
    ListElement * const tmp = new ListElement (item, 0);
    if (head == 0)
                head = tmp;
    else
                tail->next = tmp;
    tail = tmp;
}


LinkedList::LinkedList (LinkedList const& linkedList) :
    head (0),
    tail (0)
{
    ListElement const* ptr;
    for (ptr = linkedList.head; ptr != 0; ptr = ptr->next)
                Append (ptr->datum);
}


LinkedList & LinkedList::operator = (
    LinkedList const& linkedList)
{
    if (&linkedList != this)
    {
                Purge ();
                ListElement const* ptr;
                for (ptr = linkedList.head; ptr != 0; ptr = ptr->next)
                        Append (ptr->datum);
    }
    return *this;
}


void LinkedList::Delete (int const& item)
{
    ListElement* ptr = head;
    ListElement* prevPtr = 0;
    while (ptr != 0 && ptr->datum != (int) item)
    {
                prevPtr = ptr;
                ptr = ptr->next;
    }
    if (ptr == 0)
	{
        cout<<"item not found";
		return;
	}
	if (ptr == head)
                head = ptr->next;
    else
                prevPtr->next = ptr->next;
    if (ptr == tail)
                tail = prevPtr;
    delete ptr;
}


void LinkedList::InsertAfter (
    ListElement const* arg, int const& item)
{
    
    ListElement* ptr = (ListElement*) arg;
    if (ptr == 0)
    {
		cout << "Invalid Position!" <<endl;
		exit(-1);	// Exit program with return code -1
	}
    ListElement* const tmp =
                new ListElement (item, ptr->next);
    ptr->next = tmp;
    if (tail == ptr)
                tail = tmp;
}


void LinkedList::InsertBefore (ListElement const* arg, int const& item)
      
{
    ListElement* ptr = const_cast<ListElement*> (arg);

	if (ptr == 0)
	{
		cout << "Error! " << endl;
		exit(-1);	// Exit program with return code -1
	}
    ListElement* const tmp = new ListElement (item, ptr);

//Code added to deal with inserting a new head..
	if (ptr == head)
	{
		ptr = head;
		head = tmp;
		head->next = ptr;
		return;
	}
//End bug fix.
                ListElement* prevPtr = head;
                while (prevPtr != 0 && prevPtr->next != ptr)
                        prevPtr = prevPtr->next;
                        
                prevPtr->next = tmp;
}


void LinkedList::Print() 
{
        ListElement *tmp = (ListElement *) head;
        if (tmp == NULL)
            cout<<"Invalid values";
        while(tmp != 0)
		{
			cout<< tmp->datum<<endl;
			tmp = tmp->next;
		}
}


void LinkedList::Insert(int const& item)

{
 
	ListElement const* ptr = head;
    
    while(ptr != 0)
    {
		if (ptr->datum < item)
           ptr = ptr->next;
		else
        {
		   InsertBefore(ptr, item);
		   break;
		}
    } 
    if(ptr == 0)
        Append(item);
}
