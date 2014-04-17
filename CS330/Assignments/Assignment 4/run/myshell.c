/*
Assignment 3
CS 330
Chris Arnold

Run: This program takes in arguements and executes them.
		IF run without arguements, will act as a command prompt until exit is entered.

Version from Assignment 3
	- Removed pipes from bg functions. Using pid of process waiting on bg executing process.
	x
Add redirection..
*/

#include "myshellfunctions.h"
using namespace std;

int main ( int argc, char *argv[] )
{
	char delims[] = " \n";
	if( argc == 1 )		//if no args specified open as cmd prompt
	{
		int fork_id, status, counter, rtn, escape = 0, wordcount = 0;
		//timeval start, end;
		rusage c_use;
		static list <int> bg;
		const int MAXSIZE = 256;
		const int ARGMAX = 16;
		char buffer[MAXSIZE];
		char *token;
		int commands = 0;

		while( true )
		{
			commands += 1;
			rtn = -1;
			do
			{
				printf("[%d]==>", commands);
				fgets( buffer, MAXSIZE, stdin );
			} while ( buffer[0] == '\n' || buffer[0] == ' ' );

			char *temp = (char*) malloc ( strlen(buffer) * sizeof (char *) + 1);
			strcpy(temp, buffer);
			token = strtok( buffer, delims );

			do
			{
				wordcount = 0;
				escape = 0;
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
					updateBGList( bg );		//remove finished processes from list
					printBGList( bg );
				}
				else
				{
					if ( token != NULL)
						wordcount++;
					else
					{
						return 0;
					}
					while(( token=strtok(NULL,delims) ) != NULL)
						wordcount++;
					
					char *args[wordcount+1];
					for(int i = 0; i < wordcount+1; i++)
						args[i] = NULL;

					int value;
					char *temp1 = (char*) malloc ( strlen(temp) * sizeof (char *) + 1);
					strcpy(temp1, temp);
					
					value = parseArgs( args, delims, temp, wordcount );
	//		printf("value %d\n",value);
					if ( value == -1 )
						break;		//required file IO. Statement was poorly formed.
					else if ( value == -2 )
					{
	//		printf("Non-IO statement.\n");
						if( strcmp(args[wordcount-1], "&" ) == 0 )
						{
							//non-io background command
							free(args[wordcount-1]);
							args[wordcount-1] = NULL;
							fork_id = fork();
							if ( fork_id == 0 )
							{
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
									wait4(fork_id, &status, 0, &c_use);
									printf("\nBackground process %u Complete\n", fork_id);
									free(temp);
									exit(3);
								}
							}
							else
							{
								bg.push_back( fork_id );
								//main shell, 
							}
						}
						else
						{
							//non io forground command
							token = NULL;
							execRedirect(args, -1, -1, 'n', NULL, 'n'); //args, in, out, start
						}
					}
					else		//IO Redirection command
					{
						int f = fork();
						char flag_bg = 'n';
						if( strcmp(args[wordcount-1], "&") == 0 )
						{
							flag_bg = 'y';
							free(args[wordcount-1]);
							args[wordcount-1] = NULL;
							wordcount--;
						}
						if( f == -1 )
						{
							perror("FORKING ERROR");
						}
						else if( f == 0 ) {
			//			printf("calling IORedirect iwht temp: %s\n",temp1);
							rtn = IORedirect( temp1, wordcount, value, flag_bg);
							token = NULL;
							break;
						}
						else
						{
							int status;
							if( flag_bg == 'y' )
							{
								printf("Executing in background: %u\n", getpid() );
								//io redirection in bg. Add to bg task list. back to prompt
								bg.push_back( f );
							} //	else wait for io redirect cmds
							else
							{
			//					printf("Waiting for my process.\n");
								wait(NULL);
							}
							token = NULL;
						}
					}	
					for(int i = 0; i < wordcount; i++)
					{
						free(args[i]);
						args[i] = NULL;
					}
					//break;
				}
				token = strtok( NULL, delims );
				free(temp);
			}while( token != NULL );

		}
	}
	else	//run command line arguements and then quit.
	{
		int len = argc;
		int value, fork_id;
		for( int i = 1; i < argc; i++)
		{
			len += strlen(argv[i]);
		}
//		printf("length: %d\n", len);
		char *temp = (char*) malloc ( len * sizeof (char *));
		char *temp1 = (char*) malloc ( len * sizeof (char *));
		strcpy(temp, argv[1]);
		for( int i = 2; i < argc; i++)
		{
			strcat(temp, " ");
			strcat(temp, argv[i]);
		}
		strcat(temp, "\n");
	//	printf("temp: %s\n", temp);

		len = argc-1;
		char *args[argc];
			for(int i = 0; i < argc; i++)
				args[i] = NULL;
		strcpy(temp1, temp);

		value = parseArgs( args, delims, temp1, len );
	//	printf("temp: %s\n", temp);
		//change argv into string, removing first entry
		//call parseArgs
		//char *temp = (char*) malloc ( strlen(buffer) * sizeof (char *) + 1);
		//	strcpy(temp, buffer);
		//check return value to determine whether to call 
		//IORedirect or execRedirect
					if ( value == -1 )
					{
						printf("Poorly formated statement.\n");
						return 0;
					}
						//break;		//required file IO. Statement was poorly formed.
					else if ( value == -2 )
					{
		//	printf("Non-IO statement.\n");
						if( strcmp(argv[len-1], "&" ) == 0 )
						{
							//non-io background command
							free(argv[len-1]);
							argv[len-1] = NULL;
							fork_id = fork();
							if ( fork_id == 0 )
							{
								fork_id = fork();
								if ( fork_id == 0 )
								{
									printf("Executing in background: %u\n", getpid() );
									execvp( argv[1], &argv[1] );
									perror("exec failure");
									exit(1);
								}
								else 	//bg process
								{
									wait(NULL);
									printf("\nBackground process %u Complete\n", fork_id);
									free(temp);
									exit(3);
								}
							}
							else
							{
								//bg.push_back( fork_id );
								//main shell, 
							}
						}
						else
						{
							//non io forground command
							//token = NULL;
							forkMe( argv );	
							//execRedirect(argv, -1, -1, 'n', NULL); //args, in, out, start
						}
					}
					else		//IO Redirection command
					{
					//	printf("IO redirect\n");
						int f = fork();
						char flag_bg = 'n';
						if( strcmp(argv[len-1], "&") == 0 )
						{
						//	printf("BG flag set\n");
							flag_bg = 'y';
							//args[wordcount-1] = NULL;
							free(argv[len-1]);
							args[len-1] = NULL;
							//len--;
						}
						if( f == -1 )
						{
							perror("FORKING ERROR");
						}
						else if( f == 0 ) {
							int rtn;
				//			printf("calling IORedirect with %s\n",temp);
							rtn = IORedirect( temp, len, value, flag_bg);
							//token = NULL;
							//break;
						}
						else
						{
							//int status;
							if( flag_bg == 'y' )
							{
								printf("Executing in background: %u\n", getpid() );
								//io redirection in bg. Add to bg task list. back to prompt
								//bg.push_back( f );
							} //	else wait for io redirect cmds
							else
								wait(NULL);

							//token = NULL;
						}
					}	
	//	forkMe( argv );		//forks to run cmd line args
	}
	return 0;
}
