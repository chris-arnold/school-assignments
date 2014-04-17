#if !defined __MYSHELLFUNCTIONS_H__

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <list>
#include <string>
#include <fcntl.h>

using namespace std;

void printUsage( rusage , timeval, timeval);
void updateBGList( list<int>&  );			//removes process from list bg that are no longer running.
void printBGList( list<int>& );
void forkMe( char*[]);

int parseArgs( char*[], char[], char[], int);	//args, delim ,temp, wordcount
//Return greater 0 is location of pipe
//Return of -1 is error in arguements provided.
//Return of 0 is file IO required.
//Return of -2 is a statement that does not require file IO.

int IORedirect( char[], int, int, char);	//temp1, wordcount, position of @, bg(y,n)

void execRedirect(char*[], int, int, char, int[], char); //args, in, out, start, pipe_flag(n,l,r), fd[2] pipe, bg(y,n)


#endif