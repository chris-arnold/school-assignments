// flagstruct.h

#if !defined __FLAGSTRUCT_H__
#define __FLAGSTRUCT_H__

#include <stdlib.h>

#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>

using namespace std;

//structure is used to transport flag values and keep them neatly together.

struct flags{
	int pval  ;
    int sflag ;
    int Uflag ;
    int Sflag ;
    int vflag ;
    int cflag ;
    int pflag ;
	int err;		//0 is good, -1 is error
};

#endif
