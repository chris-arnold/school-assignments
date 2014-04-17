#include "myshellfunctions.h"


void updateBGList( list<int>& bg )
{
	int status;
	for ( list<int>::iterator it=bg.begin(); it!=bg.end(); ++it)
	{
		//try to wait on *it
		//int status;
		if ( waitpid(*it,&status,WNOHANG) != 0)
		{
			if ( WIFEXITED(status) || WIFSTOPPED(status) )
			{
				bg.remove( *it );
				it=bg.begin();
			}
		}
	}
}

void forkMe( char *argv[])
{
	int status;
	int fork_id;
	rusage c_use;

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

void printBGList( list<int>& bg )
{
	int counter = 1;
	if( bg.size() == 0 )
	{
		printf("There are no active background processes!\n");
		return;
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

int parseArgs( char *args[], char delims[], char temp[], int wordcount)
{
	//type = 0, file IO
	//type = -1 incorrect statement
	//type = -2 non IO statement
	//type < 0 location of pipe
//may be removing args..
	char *token;
	token = strtok( temp, delims );
	args[0] = strdup(token);
	int type = -2;
	int out = -1;
	int in = -1;
	//int flag = -1;

	for( int i = 1; i < wordcount; i++ )
	{
		token = strtok( NULL, delims );
		args[i] = strdup(token);
		//check for file re-direction
		//get next arguement. check if its a file
		if ( strcmp( token, "[" ) == 0 || strcmp( token, "]" ) == 0 || strcmp( token, "@" ) == 0 )
		{
			if ( strcmp( token, "]") == 0 )
			{
				out = 0;
				if(type < 0)
					type = 0;
			}
			if ( strcmp( token, "@") == 0 )
			{
				type = i;
				if( out == 0 )	//if output file on LHS of pipe, error
				{	printf("Cannot output LHS whilst piping.\n");
					return -1;
				}
				in = out = -1;
			}
		//	i++;
			
			if ( strcmp( token, "[" ) == 0 )
			{
				in = 0;
				if( type > 0 )	//RHS of pipe, detected input. not allowed
				{
					printf("Cannot re-direct input of RHS command whilst piping.\n");
					return -1;
				}
				else 
					type = 0;
				i++;

				if( i < wordcount )
				{
					token = strtok( NULL, delims );
					args[i] = strdup(token);
				}
				else
				{
					printf("Poorly formed statement. No file specified for re-direction.\n");
					return -1;	//no file specified for IO
				}

				struct stat st;
				if ( stat(token, &st) == -1 )	//file does not exist
				{
					printf("Poorly formed input re-direction statement.\n");
					return -1;
				}
			}
		}
	}

	return type;
}

int IORedirect( char temp[], int wordcount, int value, char bg )
{
//	printf("value: %d\n", value);
	//all looks good, exept when redirecting output from a piped
	//command, the LHS output is re-directed to the file, not
	//the RHS output.
	int start = 0;
	int start1 = -1;	//used for second pipe command
	int in = -1, out = -1, pdt = -1;
	//if value is greater than 0, we have pipe.
	char *token;
	char delims[] = " \n";
	int cmd1size;
	if(value == 0)
	{
		cmd1size = wordcount;
	}
	else
	{
		cmd1size = value+1;
	}
	int cmd2size = wordcount-value;
	char *cmd1[cmd1size];
	char *cmd2[cmd2size];
	cmd1[cmd1size] = NULL;
	cmd2[cmd2size] = NULL;
	int fd[2];

	for(int i = 0; i < cmd1size; i++)
	{
		//token = strtok(NULL, delims);
		cmd1[i] = NULL;
	}
	token = strtok(temp, delims);
	cmd1[0] = strdup(token);

	for(int i = 1; i < cmd1size; i++)
	{
		token = strtok(NULL, delims);
		cmd1[i] = strdup(token);
	}

	if( value > 0 )
	{
		for(int i = 0; i < cmd2size-1; i++)
		{
			token = strtok(NULL, delims);
			cmd2[i] = strdup(token);
		}
		cmd2[cmd2size] = NULL;
	}
	
	//prep LHS cmd
	for( int i = 0; i < cmd1size; i++ )
	{
		if( strcmp( cmd1[i], "[") == 0 )
		{
			cmd1[i] = NULL;
			i++;
			in = i;
		}
		else if( strcmp( cmd1[i], "]") == 0 )
		{
			cmd1[i] = NULL;
			i++;
			out = i;
		}
		else if( strcmp(cmd1[i], "@") == 0 )
		{
			cmd1[i] = NULL;
			i++;
		}
	}

	//if pipe cmd, open pipe. and set up.
	if( value > 0 )
	{
		if( pipe(fd) == -1)
		{
			perror("Pipe Failure");
			exit(1);
		}
		//prep for RHS cmd
		int in1 = -1;
		int out1 = -1;
		for( int i = 0; i < cmd2size-1; i++ )
		{
//			printf("cmd[%d]: %s\n", i, cmd2[i]);
			if( strcmp( cmd2[i], "[") == 0 )	//second cmd is pipe input. cannot be file.
			{	//is caught in ParseArgs
				printf("ERROR. CANNOT USE INPUT FILE.\n");
				exit(1);
				cmd2[i] = NULL;
				i++;
				in1 = i;
			}
			else if( strcmp( cmd2[i], "]") == 0 )
			{
				//printf("cmd2 output file: %s\n", cmd2[i+1]);
				cmd2[i] = NULL;
				i++;
				out1 = i;
			}
		}
//		printf("cmd1[out1]: %s cmd2[out2]: %s\n", cmd1[out], cmd2[out1]);
		cmd2[cmd2size-1] = NULL;
		//exec LHS next
		execRedirect(cmd1, in, out, 'l', fd, bg);	// l
		execRedirect(cmd2, in1, out1, 'r', fd, bg);	// r
		if( bg == 'y')
		{
			wait(NULL);
			printf("BG Command %d finished.\n", getpid());
		}
	}
	else
	{	
		execRedirect(cmd1, in, out, 'n', fd, bg);
		if( bg == 'y')
		{
			wait(NULL);
			printf("BG Command %d finished.\n", getpid());
		}
	}
	exit(0);

	return 0;
}

void execRedirect(char *args[], int in, int out, char pipe_flag, int fd[], char bg ) //args, in, out, (n) - pipe (i)nput, (o)utput
{
	int fid = fork();
	if ( fid == 0 )		//childish
	{
		if( in != -1 )
		{
			in = open( args[in], O_RDONLY ); //args[in] = NULL;
			if ( in < 0 )
			{
				perror("Open");
				exit(3);
			}
			dup2(in,fileno(stdin));		//replace stdin with infile
			close(in);
		}
		if( out != -1 )
		{
			out = open( args[out], O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
	/*		if( pipe_flag == 'r' )
			{
				//redirect output of RHS command in pipe.
				//this is currently output of LHS command.
				printf("DA SAME\n");
				fflush(stdout);
				dup2(out, fileno(stdout));
				close(fd[1]);
				close(out);
			}
			else 	*/
		//	{
				dup2(out, fileno(stdout));	//replace stdout with outfile
				close(out);
		//	}
		}
		if( pipe_flag == 'n' )
		{
			//no piping required.
		}
		else if( pipe_flag == 'l' )
		{
			dup2(fd[1], fileno(stdout));
			close(fd[1]);
			close(fd[0]);
		}
		else if( pipe_flag == 'r' )
		{
			dup2(fd[0], fileno(stdin));
			close(fd[0]);
			close(fd[1]);
		}

		execvp( args[0], &args[0] );
		perror("execvp execRedirect");
		exit(1);
	}
	else
	{
		if( pipe_flag == 'l' )
			close(fd[1]);
		else if( pipe_flag == 'r' )
			close(fd[0]);
		if( bg == 'n')
	 		wait(NULL);

		return;
	}
}


