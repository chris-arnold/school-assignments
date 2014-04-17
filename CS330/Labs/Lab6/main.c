#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

using namespace std;

int main (void)
{

        int f_des[2];
  	char *catargv[]={"cat", "colorfile.txt", NULL};
	char *sedargv[]={"sed", "-e", "s/color/colour/g", NULL};

        if (pipe(f_des)==-1)
        {
                perror("Pipe");
                exit(1);
        }
        switch (fork()) 
        {
                case -1: // fork() returned an error status, so the fork was unsuccessful. Print the associated error and terminate the program.
                        perror("Fork");
                        exit(2);
                case 0:         // We are in the child process.
                        dup2(f_des[1], fileno(stdout)); 
                        close(f_des[0]);
                        close(f_des[1]);
                        execvp(catargv[0], catargv); //where does the output of last go? The output of "last" will be written into the pipe.
                        exit(3);
                default:      // We are in the parent process.
			int fd = open("newfile.txt", O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
			dup2(fd, fileno(stdout));
                        dup2(f_des[0], fileno(stdin)); 
                        close(f_des[0]);
                        close(f_des[1]);
                        execvp(sedargv[0], sedargv); 
                        exit(4);
        }

}
