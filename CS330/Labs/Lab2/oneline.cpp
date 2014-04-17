#include "oneline.h"
#include <iostream>
#include <cstring>
#include <stdlib.h>
using namespace std;

OneLine::OneLine()
{
	oneLine = "";
	wordCount = 0;
};

OneLine::~OneLine()
{
for( int i = wordCount - 1; i >= 0; i--)
	free(words[i]); 
}

//istream &OneLine::readLine(istream& is)
void OneLine::readLine(istream& is)
{
	resetLine();
	getline(is, oneLine);
}

void OneLine::breakLine()
{
	char delim[] = " ,.-;!?";
	char *token = NULL;			//token is not allocated with malloc, strtok() deals with memory. No need to free this.
	char *temp = NULL;			//allocated with malloc. Will need to free.
	const char *temp1 = oneLine.c_str();		//copy string to cstring for use by functions like strtok(). This is a constant and doesn't need to be freed.

	temp = (char*) malloc ( strlen(temp1) * sizeof (char *)+1);

	strcpy(temp, temp1);
	token = strtok(temp, delim);

	if (token != NULL)		//if line read in has no tokenable values, free mem and return
		wordCount++;
	else
	{
		free(temp);
		return;
	}

	while((token=strtok(NULL,delim)) != NULL)		//count the words
		wordCount++;

	words = new char* [wordCount];		
	strcpy(temp, temp1);				//re-copy master line onto temp

	token = strtok(temp, delim);
	words[0] = strdup(token);
	
	for( int i = 1; i < wordCount; i++)
	{
		token = strtok(NULL,delim);
		words[i] = strdup(token);
	}

	free(temp);
}

string OneLine::returnLine()
{
	return oneLine;
}

void OneLine::printReverse()
{
	for(int i = wordCount-1; i >= 0; i--)
		cout << words[i] << " ";
	cout << endl;
}

void OneLine::resetLine()		//reset words[], oneLine and wordCount
{
if(wordCount > 0)
{
	for(int i = wordCount-1; i >=0; i--)
		free(words[i]);

	delete [] words;

	oneLine = "";
	wordCount = 0;
}
}
