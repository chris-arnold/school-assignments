#include <ctype.h>
#include <unistd.h>
#include "testgetopt.h"
     
struct flags
getopts (int argc, char *argv [])
{
	struct flags a;
	a.pval  = -1;
    a.sflag = 0;
     a.Uflag = 0;
     a.Sflag = 0;
     a.vflag = 0;
     a.cflag = 0;
     a.pflag = 0;
	 a.err   = 0;	
    char *pvalue = NULL;
    int index;
    int c;
     
    opterr = 0;
     
    while ((c = getopt (argc, argv, "sUSvcp::")) != -1)
    {
        switch (c)
        {
            case 's': a.sflag = 1;
                      break;
            case 'U': a.Uflag = 1;
                      break;
      		case 'S': a.Sflag = 1;
      				  break;
      		case 'v': a.vflag = 1;
      				  break;
      		case 'c': a.cflag = 1;
	  	             break;
            case 'p': a.pflag = 1;
					  pvalue = optarg;
                      break;
            case '?': if (isprint (optopt))
                          fprintf (stderr, "Unknown option `-%c'.\n", optopt);
                      else
                          fprintf (stderr, "Unknown option character `\\x%x'.\n", optopt);
					  a.err = -1;
                      return a;
            default: abort ();
        }
    }
	if ( pvalue != NULL )
		a.pval = atoi(pvalue);
	
     
    for (index = optind; index < argc; index++)
        printf ("Non-option argument %s\n", argv[index]);

	
//if no flags selected, mark all as selected	
	if ( a.pflag == 0 && a.sflag == 0 && a.Uflag ==0 && a.Sflag ==0 && a.vflag ==0 && a.cflag == 0 )
		a.sflag = a.Uflag = a.Sflag = a.vflag = a.cflag = 1;

    return a;
}
