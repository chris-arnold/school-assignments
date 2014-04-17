#include "testreaddir.h"
#include "getFlagInfo.h"

using namespace std;

int readdir ( struct flags c)
{
/*
	My added variables:
	char status		- char to hold status from function call if required
	char *cmd		- to hold cmd string from function call if required
	long utime		- to hold user time
	long stime		- to hold system time
	long vmSize		- to hold vm size in pages
	int count		- flag to trigger specific event of PID being specified, but not found. To output message
*/
    DIR *dirp;
    struct dirent *dp;
    FILE *fp;
    char *envFileName, status, *cmd;
	long utime, stime, vmSize;
	int count = 0;

    dirp = opendir ("/proc");
    while (dirp)
    {
        if ((dp = readdir (dirp)) != NULL)
        {
            if (atoi (dp -> d_name))
            {
                envFileName = (char *) malloc (strlen (dp -> d_name) * sizeof (char *) + 14);
                strcpy (envFileName, "/proc/");
                strcat (envFileName, dp -> d_name);
                strcat (envFileName, "/environ");
                fp = fopen (envFileName, "r");
                if (!fp)
                {
				//dont care about these
                   // printf ("%s not one of my processes!\n", dp -> d_name);
                }
                else
                {
					if ( c.pflag == 1 && c.pval > 0 )		//if pflag and pvalue are specified, check if folder name matches, else get all
					{
						if ( atoi( dp -> d_name) == c.pval )
						{
							printf ("%s\t", dp->d_name);
							if (c.sflag == 1)
							{
								status = getState( dp -> d_name ) ;
								printf ("%c\t", status);
							}
							if (c.Uflag == 1)
							{
								utime = getUserTime( dp->d_name );
								printf ("%lu\t\t", utime);
							}
							if (c.Sflag == 1)
							{
								stime = getSysTime( dp->d_name );
								printf ("%lu\t\t", stime);
							}
							if (c.vflag == 1)
							{
								vmSize = getVM( dp->d_name );
								printf ("%lu\t\t", vmSize);
							}
							if (c.cflag == 1)
							{
								cmd = getcmd( dp->d_name );
								printf ("%s", cmd);
							}
							printf ("\n");
							return 0;
						}
					}
					else
					{
						fclose (fp);
						printf ("%s\t", dp->d_name);
						if (c.sflag == 1)	//check for each flag. print to screen if selected in pre-determined order
						{
							status = getState( dp -> d_name ) ;
							printf ("%c\t", status);
							}
						if (c.Uflag == 1)
						{
							utime = getUserTime( dp->d_name );
							printf ("%lu\t\t", utime);
						}
						if (c.Sflag == 1)
						{
							stime = getSysTime( dp->d_name );
							printf ("%lu\t\t", stime);
						}
						if (c.vflag == 1)
						{
							vmSize = getVM( dp->d_name );
							printf ("%lu\t\t", vmSize);
						}
						if (c.cflag == 1)
						{
							cmd = getcmd( dp->d_name );
							printf ("%s", cmd);
						}
						printf ("\n");
						count = 1;		//to check that a pid was actually found
					}
                }
                free (envFileName);
            }
        }
        else
        {
            break;
        }
    }
    closedir (dirp);
	if ( count == 0 )
		return -1;
	else
		return 0;
}
