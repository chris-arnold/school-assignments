/*
Assignment 3
CS 330
Chris Arnold

Run: This program takes in arguements and executes them.
		IF run without arguements, will act as a command prompt until exit is entered.

Oct 13 - Initial version complete.

Known Issues:
	- (SOLVED)Hitting the return key without any other input, or a space character results in a crash.
		->Reject input beginning with either of these delimiting characters.
	- (SOLVED)bg does not list all background processes, although there are some running.
	- (SOLVED)Elapsed time should be updated to real time to complete
	- (SOLVED)exit command needs to reject exit if bg processes are active
		->bg needs to be executed to clear list. Must adjust.
	- (SOLVED)cpu time to be in ms
	- (SOLVED)CPU time is just summing to itself instead of just returning what it did
		-(Edit) all stats from getrusage are doing this
		-SOLUTION - instead of using getrusage with anything, used wait4( fork_id, status, 0, rusage struct). this waits for the forked process and gets the usage information for ONLY that process.

*/

#include "myshellfunctions.h"
using namespace std;

int main ( int argc, char *argv[] )
{
	if( argc == 1 )		//if no args specified open as cmd prompt
	{
		int fork_id, status, counter, wordcount = 0;
		timeval start, end;
		rusage c_use;
		static list <int> bg;
		const int MAXSIZE = 256;
		const int ARGMAX = 16;
		char buffer[MAXSIZE];
		char delims[] = " \n";
		char *token;

		while( true )
		{
			do
			{
				write(1, "==>", 3);
				fgets( buffer, MAXSIZE, stdin );
			} while ( buffer[0] == '\n' || buffer[0] == ' ' );

			char *temp = (char*) malloc ( strlen(buffer) * sizeof (char *) + 1);
			strcpy(temp, buffer);
			token = strtok( buffer, delims );

			do
			{
				wordcount = 0;
				if( strcmp( token, "exit" ) == 0 )
				{
					updateBGList( bg );		//need to update list of bg processes before attempting to exit
					if( bg.size() == 0 )
					{
						free(temp);
						exit(1);
					}
					else
					{
						printf("There is still %u background process active. Cannot exit.\n", bg.size());
						break;
					}
				}
				else if( strcmp( token, "cd" ) == 0)
				{
					char *pwd;
					pwd = strtok( NULL, "\n" );
					if( chdir(pwd) != 0 )
					{
						perror("Error changing directory");
						break;
					}
					else
					{
						printf("Directory successfully changed to %s\n", pwd); 
						break;
					}
				}
				else if( strcmp( token, "bg" ) == 0 )
				{
					counter = 1;
					updateBGList( bg );		//remove finished processes from list

					if( bg.size() == 0 )
					{
						printf("There are no active background processes!\n");
						break;
					}
					else
					{
						printf("Background Processes:\n");
					}
					//then print out what is left marked as active
					for ( list<int>::iterator it=bg.begin(); it!=bg.end(); ++it)
					{
						printf("[%u] %u\n", counter, *it);
						counter += 1;
					}

				}
				else
				{
					if ( token != NULL)
						wordcount++;
					else
					{
						//free(temp);
						return 0;
					}
					while(( token=strtok(NULL,delims) ) != NULL)
						wordcount++;

					char *args[wordcount];
					for(int i = 0; i < wordcount; i++)
						args[wordcount] = NULL;

					token = strtok( temp, delims );
					args[0] = strdup(token);

					for( int i = 1; i < wordcount; i++ )
					{
						token = strtok( NULL, delims );
						args[i] = strdup(token);
					}

					//free(temp);

					if ( strcmp( args[wordcount-1], "&" ) == 0)
					{
						int fd[2];		//shell needs its grandchilds pid. will get from this pipe.
						pipe(fd);

						free(args[wordcount-1]);
						args[wordcount-1] = NULL;
						fork_id = fork();
						if ( fork_id == 0 )
						{
							gettimeofday(&start, NULL);
							fork_id = fork();
							if ( fork_id == 0 )
							{
								printf("Executing in background: %u\n", getpid() );
								execvp( args[0], &args[0] );
								perror("exec failure");
								exit(1);
							}
							else 	//bg process
							{
								char *thing = NULL;
								thing = (char*) malloc ( sizeof (int ) + 1);
								sprintf(thing, "%d", fork_id );	//convert pid executing argv in background to string to send in pipe
								close(fd[0]);
							    write(fd[1], thing, ( sizeof( int ) ) + 1);
							    free(thing);
								
								wait4(fork_id, &status, 0, &c_use);
								gettimeofday(&end, NULL);
								printf("\nBackground process %u Complete\n", fork_id);
								printUsage( c_use, start, end);
								free(temp);
								exit(1);
							}
						}
						else
						{
							//main shell, 
						}

						//back to parent..read pipe and add to list
						int rBytes, value;
						char rBuffer[(sizeof(int))+1];
						close(fd[1]);
						rBytes = read( fd[0], rBuffer, sizeof(rBuffer));
						close(fd[0]);
						value = atoi( rBuffer );
						bg.push_back( value );
					}
					else 	//fg process
					{
						gettimeofday(&start, NULL);
						fork_id = fork();
						if ( fork_id == 0 )
						{
							execvp( args[0], &args[0]);
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

					for(int i = 0; i < wordcount; i++)
					{
						free(args[i]);
						args[i] = NULL;
					}
					break;
				}
				token = strtok( NULL, delims );
				free(temp);
			}while( token != NULL );

		}
	}
	else	//run command line arguements and then quit.
	{
		forkMe( argv );		//forks to run cmd line args
	}
	return 0;
}
