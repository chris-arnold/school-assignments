// getFlagInfo.h

#if !defined __GETFLAGINFO_H__
#define __GETFLAGINFO_H__
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>

//#include <time.h>

using namespace std;

char getState( char *pid ) ;	//reads stat file to get pid status

long getUserTime( char *pid ); //reads stat file for user time

long getSysTime( char *pid );	 //reads stst file for sys time

long getVM( char *pid );		 //reads statm for virtual mem usage

char *getcmd( char *pid );		//reads cmdline for cmd used

#endif
