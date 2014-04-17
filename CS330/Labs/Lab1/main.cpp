#include<iostream>
#include"LinkedList.h"
using namespace std;

int main()
{

  char choice=0;
  int item;
  LinkedList a;

  cout << "This program demonstrates the linked list. " << endl;
  cout << "Initially, the list contains 3 integers: 1,3,and 5." << endl;
  cout << "You can use the following command to manipulate the list." <<endl << endl;
 
  a.Insert(1);
  a.Insert(3);
  a.Insert(5);


  while(choice != 'q')
  {
    cout << "*******************************************************" << endl;
	cout<<"i: Insert (Insert an element and keep the list ordered)\n";
    cout<<"d: Delete (Delete a node with the given value)\n";
    cout<<"p: Print  (Print the content of the current list)\n";
    cout<<"q: Quit   (Quit the program)\n";
    cout << "*******************************************************" << endl << endl;
    cout<<"\n Please enter your choice here:";
    cin>>choice;
		
    switch(choice)
    {
      case 'i':
        cout<<"Please enter an integer to insert:";
	    cin>>item;
	  
	    if (item < 0)
		{
	       cout<<"\n Please try again:";
	       cin>>item;
		}

	    a.Insert(item);
	  
	    break;
      case 'd':
	    cout<<"\n Please enter an integer value to delete:";
	    cin>>item;
	    if (item < 0)
        {
	       cout<<"\n Please try again:";
	       cin>>item;
		}

	    a.Delete(item);		
	    break;
      case 'p':
		  cout << "The content of the current ordered list is: "<<endl;
		  a.Print();
	    break;
      case 'q':
	    break;
      default:
	    cout<<"\n Invalid choice. Please try again.\n";
	    break;
    }
  }
  cout<<"\n Bye\n";
  return 0;
}	
