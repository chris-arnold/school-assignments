#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/wait.h>
#include <stdlib.h>

using namespace std;

int main ( int argc, char *argv[] )
{
	pid_t fork_id;
	int status;

	if( argc != 2 )
	{
		printf("Must enter one command line arguement to cat\n");
		exit(0);
	}

	fork_id = fork();

	if ( fork_id == 0 )
	{

		printf("In the CHILD process\n");
		printf("Child Process ID: %d, Parent ID: %d, Process Group: %d\n", getpid(), getppid(), getpgrp());

		/*
		execl( "/bin/cat\0", "/usr/bin/cat -b -v -t\0", argv[1], NULL );
		perror("exec failure");
		exit(1);
		*/

		
		char *cmd[] = { (char*)"cat", (char*) "-b", (char*)"-v", (char*)"-t" , argv[1], (char*)0 };
		execv( "/bin/cat", cmd);
		perror("exec failure");
		exit(1);
		
	}
	else
	{
		wait(&status);
		printf("In the PARENT process\n");
		printf("Original Process ID: %d, Parent ID: %d, Process Group: %d\n", getpid(), getppid(), getpgrp());
	}

}
