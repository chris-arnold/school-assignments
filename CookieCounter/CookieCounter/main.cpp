/*
CookieCounter reads the input file. Mines the data into an array of structures(which contain an unsorted list, class id.
To modify number of classes, or students in the class, the constants in ClassInfo.h and Definitions.h must be updated, then
the input file to match. 
*/

#include "ClassInfo.h"
#include <fstream>
#include <iomanip>
//main program functions that are offloaded to make main easier to read and follow

const int columnWidth = 15;			//merely for formating the individual team sales to the user
void printMenu();		//pre - N/A. Post - User menu is printed to screen for users assistance.
bool validID(int classid);
int main()
{
	//main variables
	classInfo cookieClass[numberOfClasses];
	int mostCookiesSold = 0;			//used to figure out the winner of the sales competition
	char wtd;			//what to do. Collects input from the user for requested action

	//taking care of filestreams
	ifstream input;					//opening input filestream to input.txt
	input.open("input.txt", ios::in);	//opening is input stream only!, checking to see if file was successfully opened. if not, program aborts.
	if(!input.is_open())
	{
		cerr << "The input file input.txt could not be successfully opened. This is vital to the operation of the program. "
			<< "This program is been aborted :( " << endl;
		return 1;
	}

	ofstream output;				//opening output stream to boxes.out
	output.open("boxes.out", ios::out | ios::trunc);		//opened as output stream only. If file has any existing data in it, its erased and rewritten.
			//I dont check to see if output file has been opened, because it is created if it doesn't exist.
			//I suppose I could for redundancy and whatnot...seems pointless.

	//initalizing class information
	for(int i = 0; i < numberOfClasses; i++)	
	{
		cookieClass[i].totalSoldCookies = 0;
		input >> cookieClass[i].classID;			//first number of each line in input.txt holds class id
		Type temp;
		input >> temp;
		while(temp != -1)			//read numbers until end of line. -1 is used to notate end of line in input file. 
		{	
			cookieClass[i].cookies.insertItem(temp);
			input >> temp;
		}
	}

	//now that the file streams have been opened, and the input files data imported into the lists, we can open the menu to the user and allow them to modify the data as wished.
	printMenu();
	do{
		cout << "What would you like to do? ";
		cin >> wtd;
		int classid;
		Type item;
		bool found = false;
		switch (wtd)
		{
			case 'l':
				//query user as to which class length they would want
				cout << "What class would you like get the length of? ";
				cin >> classid;
				classid = classid-1;	//classid's are 1-10. Arrays are indexed 0-9. This makes everything work together!
				if(validID(classid))
				{
				cout << "The length requested is: " << cookieClass[classid].cookies.lengthIs() << endl << endl; // call lengthis for appropriate class
				}
				break;
			case 'r':
				cout << "What item would you like to look for? ";
				cin >> item;
				cout << "And for what class? ";
				cin >> classid;
				classid = classid-1;
				if(validID(classid))
				{
				//query user as to which class they'd like to retrieve from
				//ask for item to look for
				cookieClass[classid].cookies.retrieveItem(item, found);
				cout << "The item " << item << " was ";
				if(found)
					cout << "found in the list. ";
				else
					cout << "not found in the list. ";
				cout << endl << endl;
				}
				//output results
				break;
			case 'd':
				cout << "What item would you like to delete? ";
				cin >> item;
				cout << "And from what class? ";
				cin >> classid;
				classid = classid-1;
				if(validID(classid))
				{
				cookieClass[classid].cookies.deleteItem(item);
				//query user as to which class they'd like to delete from
				//ask for item to delete
				//output results
				}
				cout << endl;
				break;
			case 'e':
				cout << "What class would you like to empty? ";
				cin >> classid;
				classid = classid-1;
				if(validID(classid))
				{
				cookieClass[classid].cookies.resetList();
				//query user as to which class they'd like to empty
				//reset list
				}
				cout << endl;
				break;
			case 'i':
				cout << "What item would you like to insert? ";
				cin >> item;
				cout << "And from what class? ";
				cin >> classid;
				classid = classid-1;
				if(validID(classid))
				{
				cookieClass[classid].cookies.insertItem(item);
				//query user as to which class they'd like to insert a value into
				//insertItem fn outputs any errors if they occur.
				}
				cout << endl;
				break;
			case 'm':
				printMenu();
				break;
			case 'p':
				//query user as to which class they'd like to print out sales information for
				cout << "What class would you like to print the sales record for? ";
				cin >> classid;
				classid = classid-1;
				if(validID(classid))
				{
				for(int i = 0; i < cookieClass[classid].cookies.lengthIs(); i++)
				{
					if((i % 4) == 0)				//makes columns of 4. much easier to read than scrolling threw 20 lines :)
					{
						cout << endl << setw(columnWidth)
							<< cookieClass[classid].cookies.getItem(i) << " ";
					}
					else
						cout << setw(columnWidth) << cookieClass[classid].cookies.getItem(i) << " ";
				}
				cout << endl << endl;
				}
				break;
			case 'q':
				break;		//will just skip to condition of while loop and continue running the program
			default:
				cout << "The choice you entered is invalid. Please try again: ";			//incorrect inputs happen. may as well be polite about it.
				break;
		}
	}while (wtd != 'q');

	//calculate sums
	for(int i = 0; i < numberOfClasses; i++)
	{
		for(int j = 0; j < MAXSIZE; j++)
		{
			cookieClass[i].totalSoldCookies += cookieClass[i].cookies.getItem(j);
		}
		if(cookieClass[i].totalSoldCookies > mostCookiesSold)			//as we sum the cookies sold, we keep track of the most cookies sold. Will be used to find winner(s). May as well kill 2 birds with one stone
			mostCookiesSold = cookieClass[i].totalSoldCookies;
	}

	//starting to output data to boxes.out
	output << "The total number of boxes sold by the classes: " << endl
		<< setw(columnWidth) << "Class ID: " << setw(columnWidth) << "Boxes sold: " << endl;
	for(int i = 0; i < numberOfClasses; i++)
	{
		output << setw(columnWidth) << cookieClass[i].classID << setw(columnWidth) << cookieClass[i].totalSoldCookies << endl;
	}
	output << endl << endl
		   << "The winner(s) of the cookie sales competition is(are): " << endl;
	for(int i = 0; i < numberOfClasses; i++)
	{
		if(cookieClass[i].totalSoldCookies == mostCookiesSold)
		{
			output << "Class " << cookieClass[i].classID << endl;
		}
	}
	output << "Congratulations to the winners!! " << endl << endl;
	
	//now to show retention of sales
	output << endl << endl << "The inputed data is as follows: " << endl;
	for(int i = 0; i < numberOfClasses; i++)
	{
		output << "Class " << cookieClass[i].classID << " sold the following numbers of cookies: " << endl;
		for(int j = 0; j < MAXSIZE; j++)
			output << cookieClass[i].cookies.getItem(j) << endl;
	output << endl;
	}

	input.close();					//closing filestream
	output.close();					//closing filestream

	return 0;
}					//END MAIN!!!!


/*  Would love to use these and make main look cleaner, but for some reason, the functions below with appropriate 
prototypes didn't work properly :(. Oh well. Exact same code minus the functions in main work just as good I suppose.

-----------------------------------------------------------------------

 Function definitions for use in main function

 ------------------------------------------------------------------------ */

//void calculateSums(classInfo cookieClass[], int & mostCookiesSold)
//{
//	for(int i = 0; i < numberOfClasses; i++)
//	{
//		for(int j = 0; j < MAXSIZE; j++)
//		{
//			cookieClass[i].totalSoldCookies += cookieClass[i].cookies.getItem(j);
//		}
//		if(cookieClass[i].totalSoldCookies > mostCookiesSold)			//as we sum the cookies sold, we keep track of the most cookies sold. Will be used to find winner(s)
//			mostCookiesSold = cookieClass[i].totalSoldCookies;
//	}
//
//}
//
//void initializeClasses(classInfo cookieClass[], ifstream input)
//{
//	for(int i = 0; i < numberOfClasses; i++)	
//	{
//		cookieClass[i].totalSoldCookies = 0;
//		input >> cookieClass[i].classID;			//first number of each line in input.txt holds class id
//		Type temp;
//		input >> temp;
//		while(temp != -1)			//read numbers until end of line. -1 is used to notate end of line in input file. 
//		{	
//			cookieClass[i].cookies.insertItem(temp);
//			input >> temp;
//		}
//	}
//
//}

//void printResults(classInfo cookieClass[], ofstream output, int & mostCookiesSold)
//{
//	output << "The total number of boxes sold by the classes: " << endl
//		<< setw(columnWidth) << "Class ID: " << setw(columnWidth) << "Boxes sold: " << endl;
//	for(int i = 0; i < numberOfClasses; i++)
//	{
//		output << setw(columnWidth) << cookieClass[i].classID << setw(columnWidth) << cookieClass[i].totalSoldCookies << endl;
//	}
//	output << endl << endl
//		<< "The winner(s) of the cookie sales competition is(are): " << endl;
//	for(int i = 0; i < numberOfClasses; i++)
//	{
//		if(cookieClass[i].totalSoldCookies == mostCookiesSold)
//		{
//			output << "Class " << cookieClass[i].classID << endl;
//		}
//	}
//	output << "Congratulations to the winners!! " << endl << endl;
//}

//void printSalesNumbers(classInfo cookieClass[], ofstream output)
//{
//	output << endl << endl << "The inputed data is as follows: " << endl;
//	for(int i = 0; i < numberOfClasses; i++)
//	{
//		output << "Class " << cookieClass[i].classID << " sold the following numbers of cookies: " << endl;
//		for(int j = 0; j < MAXSIZE; j++)
//			output << cookieClass[i].cookies.getItem(j) << endl;
//	output << endl;
//	}
//
//}


/*functions for main. First one just prints out a menu to the user.
second one error checks the class id inputed. Eliminates a cause of program crash during runtime. 
*/
void printMenu()
{
	cout << "|----------------------------------|" << endl
		 << "|             The Menu             |" << endl
		 << "|For the length of the list      l |" << endl
		 << "|To retrieve an item             r |" << endl
		 << "|To delete an item               d |" << endl
		 << "|To reset the list               e |" << endl
		 << "|To insert an item               i |" << endl
		 << "|To quit the program             q |" << endl
		 << "|To see this menu                m |" << endl
		 << "|To print team sales             p |" << endl
		 << "|----------------------------------|" << endl;

}

bool validID(int classid)
{
	if(0 < classid && classid < numberOfClasses)
		return true;
	else
	{
		cout << "Class ID is invalid. Please pick another menu option. " << endl;
		return false;
	}
}
