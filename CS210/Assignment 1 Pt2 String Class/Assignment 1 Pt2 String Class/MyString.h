#ifndef MYSTRING_H
#define MYSTRING_H

class MyString	
{
private:
         char *pData;		//pointer to simple C-style representation of the string
							//(i.e., sequence of characters terminated by null)
							//pData is only a pointer. You must allocate space for 
							//the actual character data
         int length;		//length of the string
							// …
        					//possible other private data

public:
     MyString();				//constructor --- create empty string
     MyString(char *cString);	//constructor --- create a string whose data is a copy of
								//cString
    ~MyString();				//destructor -- don't forget to free space allocated by the constructor
								//i.e., the space allocated for the character data

     MyString(MyString const& s);	//override the default copy constructor --- why?
									//important -- think about it -- possible test question
     MyString& operator = (MyString const& s);  //override default assignment operator
     void Put();		//output string
     void Reverse();	//reverse the string
     
     MyString& operator + (MyString const& s);   //concatenation operator
     // …					       //other useful member functions 
						       //as you wish
};

#endif   // MYSTRING_H
