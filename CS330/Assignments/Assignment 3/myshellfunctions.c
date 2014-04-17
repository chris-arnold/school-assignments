#include "myshellfunctions.h"


void updateBGList( list<int>& bg )
{
	for ( list<int>::iterator it=bg.begin(); it!=bg.end(); ++it)
	{
	char *thing = NULL;
	thing = (char*) malloc ( sizeof (int ) + 1 + (6 * sizeof(char*) + 1));
	sprintf(thing, "/proc/%d\0", *it );
	struct stat st;
	if ( stat(thing, &st) != 0 )
	{
		bg.remove( *it );
		it = bg.begin();
	}
	free(thing);
	}
}

void forkMe( char *argv[])
{
	int status;
	timeval start, end;
	int fork_id;
	rusage c_use;
		gettimeofday(&start, NULL);

		fork_id = fork();
		if ( fork_id == 0 )
		{
			execvp( argv[1], &argv[1]);
			perror("exec failure");
			exit(1);
		}
		else
		{
			wait4(fork_id, &status, 0, &c_use);
			gettimeofday(&end, NULL);
			printUsage( c_use, start, end);
		}
}

void printUsage( rusage c_use, timeval start, timeval end )
{
	long seconds, useconds, etime, c_time;
	seconds = end.tv_sec - start.tv_sec;
	useconds = end.tv_usec - start.tv_usec;
	etime = ((seconds) * 1000 + useconds/1000.0) + 0.5;
	c_time = (((c_use.ru_utime.tv_sec) * 1000) + ((c_use.ru_utime.tv_usec) / 1000) ) + 0.5;

	printf("------------------------------------\n");
	printf("CPU Time %ldms, Elapsed time: %ldms\n", c_time, etime);
	printf("Preempted Involuntarily %lu. Number of voluntary CPU give up %lu\n", c_use.ru_nivcsw, c_use.ru_nvcsw );
	printf("Page Faults %lu, Non-disk I/O page Fault %lu.\n", c_use.ru_majflt, c_use.ru_minflt );
}