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

using namespace std;

void printUsage( rusage , timeval, timeval);
void updateBGList( list<int>&  );			//removes process from list bg that are no longer running.

void forkMe( char*[]);

#endif