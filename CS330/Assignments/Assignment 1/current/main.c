#include "testgetopt.h"
#include "testreaddir.h"
     
int
main (int argc, char *argv [])
{
	
    struct flags f;
	int ret;

    f = getopts( argc, argv );			//process args. results are returned in flags structure
	
	if ( f.err == 0 )
	{
	//print header
	printf ("PID:");
	if (f.sflag == 1)
		printf ("\tStatus:");
	if (f.Uflag == 1)
		printf ("\tUser Time:");
	if (f.Sflag == 1)
		printf ("\tSys Time:");
	if (f.vflag == 1)
		printf ("\tVM Size:");
	if (f.cflag == 1)
		printf ("\tCMD:");
	
	printf ("\n");
	
	ret = readdir( f );	//processes opts, gets information from files, and prints them out.
	
	if ( ret == -1 )	//if p flag and pval specified, but the pid doesn't exist
		printf ("The PID %d was not found.\n", f.pval);
		
	}
	else
	{
		printf ("Error flag set in getopts\n");
	}

    return 0;
}

