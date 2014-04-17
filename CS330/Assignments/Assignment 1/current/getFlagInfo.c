//getFlagInfo.c
#include "getFlagInfo.h"

using namespace std;

char getState( char *pid )		//returns char holding state of the process
{
	FILE *fp;
	DIR *dirp;
	char *fileName,*dirName;
	
	fileName = (char*) malloc ( strlen (pid) * sizeof (char *) + 10);
	dirName = (char*) malloc ( strlen (pid) * sizeof (char *) + 6);

	strcpy( dirName, "/proc/");
	strcat( dirName, pid);
	strcpy( fileName, "/proc/");
	strcat( fileName, pid );
	strcat( fileName, "/stat" );
	
	dirp = opendir (dirName);
	
	if(dirp) 
	{
		fp = fopen (fileName, "r");
		if (!fp)
		{
			printf ("could not open file %s\n", fileName );
			closedir(dirp);
			return 'e';
		}
		else
		{
			char val;
			fscanf(fp, "%*d %*s %c", &val);		//scan beginning of file, disregard pid, string, but grab next char
			fclose (fp);
			closedir(dirp);
			return val;
		}
	}
	else
	{
		printf ("Failure opening directory %s\n", dirName);
		return 'f';	
	}

};


long getUserTime( char *pid )		//returns number of seconds process spend in user mode
{
	long uTime = -1;
	FILE *fp;
	DIR *dirp;
	char *fileName,*dirName;
	
	fileName = (char*) malloc ( strlen (pid) * sizeof (char *) + 10);
	dirName = (char*) malloc ( strlen (pid) * sizeof (char *) + 6);

	strcpy( dirName, "/proc/");
	strcat( dirName, pid);
	strcpy( fileName, "/proc/");
	strcat( fileName, pid );
	strcat( fileName, "/stat" );
	
	dirp = opendir (dirName);
	
	if(dirp) 
	{
		fp = fopen (fileName, "r");
		if (!fp)
		{
			printf ("could not open file %s\n", fileName );
		}
		else
		{
			//user time is 14th field in and of type long. disregard everything else
			fscanf(fp, "%*d %*s %*c %*d %*d %*d %*d %*d %*u %*u %*u %*u %*u %lu", &uTime);
			fclose (fp);
		}
	}

	closedir(dirp);
	return uTime;
};


long getSysTime( char *pid )			//reads stat file for sys time
{
	long uTime = -1;
	FILE *fp;
	DIR *dirp;
	char *fileName,*dirName;
	
	fileName = (char*) malloc ( strlen (pid) * sizeof (char *) + 10);
	dirName = (char*) malloc ( strlen (pid) * sizeof (char *) + 6);
	
	strcpy( dirName, "/proc/");
	strcat( dirName, pid);
	strcpy( fileName, "/proc/");
	strcat( fileName, pid );
	strcat( fileName, "/stat" );
	
	dirp = opendir (dirName);
	
	if(dirp) 
	{
		fp = fopen (fileName, "r");
		if (!fp)
		{
			printf ("could not open file %s\n", fileName );
		}
		else
		{
			//user time is 15th field in and of type long. ignore all else
			fscanf(fp, "%*d %*s %*c %*d %*d %*d %*d %*d %*u %*u %*u %*u %*u %*u %lu", &uTime);				
			fclose (fp);
		}
	}

	closedir(dirp);
	return uTime;
};	 

long getVM( char *pid )			//reads statm for virtual mem usage
{
	long vmSize = -1;
	FILE *fp;
	DIR *dirp;
	struct dirent *dp;
	char *fileName,*dirName;
	
	fileName = (char*) malloc ( strlen (pid) * sizeof (char *) + 10);
	dirName = (char*) malloc ( strlen (pid) * sizeof (char *) + 7);

	strcpy( dirName, "/proc/");
	strcat( dirName, pid);
	strcpy( fileName, "/proc/");
	strcat( fileName, pid );
	strcat( fileName, "/statm" );
	
	dirp = opendir (dirName);
	
	if(dirp) 
	{
		fp = fopen (fileName, "r");
		if (!fp)
		{
			printf ("could not open file %s\n", fileName );
		}
		else
		{
			//total program size is first element in file of type long. Get it.
			fscanf(fp, "%lu", &vmSize);		
			fclose (fp);

		}
	}

	closedir(dirp);
	return vmSize;
};

char *getcmd( char *pid )			//reads cmdline for cmd used
{
	char *cmd;
	FILE *fp;
	DIR *dirp;
	char *fileName,*dirName;
	
	fileName = (char*) malloc ( strlen (pid) * sizeof (char *) + 12);
	dirName = (char*) malloc ( strlen (pid) * sizeof (char *) + 7);

	strcpy( dirName, "/proc/");
	strcat( dirName, pid);
	strcpy( fileName, "/proc/");
	strcat( fileName, pid );
	strcat( fileName, "/cmdline" );
	
	dirp = opendir (dirName);
	
	if(dirp) 
	{
		fp = fopen (fileName, "r");
		if (!fp)
		{
			printf ("could not open file %s\n", fileName );
		}
		else
		{
			//this file only contains the command string. get it.
			fscanf(fp, "%s", cmd);		
			fclose (fp);
		}
	}

	closedir(dirp);
	return cmd;
};
