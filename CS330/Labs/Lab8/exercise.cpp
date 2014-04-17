/* Taken from Interprocess Communications in UNIX, page 184-187 */
 /*
* First section -- producer/consumer problem
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#define BUFFER "./buffer"

/* This declaration is "MISSING" in many Solaris environments
   It should be included in the <sys/sem.h> file but often is not! If you
   receive a duplicate definition error message for semun then comment 
   out this declaration
*/

union semun
{
   int			val;
   struct  semid_ds	*buf;
   unsigned short  	*array;
   struct seminfo	*__buf;	//Linux specific: for IPC_INFO
};

main(int argc, char *argv[])
{
   FILE			*fptr;
   static struct	sembuf  acquire = {0, -1, SEM_UNDO},
				release = {0,  1, SEM_UNDO};
   pid_t		c_pid;
   key_t		ipc_key;
   static ushort	start_val[2] = {1, 0};
   int			semid, producer = 0, i, n, p_sleep, c_sleep;
   union semun		arg;
   enum { CHILD, PARENT };
   if (argc != 2)
   {
      fprintf(stderr, "%s sleep_time \n", argv[0]);
      exit(-1);
   }

   ipc_key = ftok(".", 'S');
   if ((semid=semget(ipc_key, 2, IPC_CREAT|IPC_EXCL|0666)) != -1)
   {
      producer = 1;
      arg.array = start_val;
      if (semctl(semid, 0, SETALL, arg) == -1)
      {
         perror("semctl -- producer -- initialization\n");
         exit(1);
      }
   }
   else if ((semid = semget(ipc_key, 2, 0)) == -1)
   {
      perror("semget -- consumer -- obtaining semaphore");
      exit(2);
   }
   
   if ( (fptr = fopen(BUFFER, "r+")) == NULL )
   {
	perror("Opening Buffer");
	exit(6);
   }
   fprintf(fptr, "0\n");
   fclose(fptr);


/*
* Second section of the producer/consumer problem
*/
int fork_id = fork();

   if( fork_id != 0 )
   {		/* The producer */
      p_sleep = atoi(argv[1]);
      srand((unsigned) getpid());
      sleep(2);      //delay parent so child goes first
      for ( ; ; )
      {
         sleep(p_sleep);
         acquire.sem_num = PARENT;
         if (semop(semid, &acquire, 1) == -1)
         {
            perror("semop -- parent -- waiting for consumer to WRITE number");
            exit(3);
         }
      	if( (fptr = fopen(BUFFER, "rw+") ) == NULL )
      	{
      		perror("Opening buffer.");
      		exit(5);
      	}
      	
         //n = rand() %99 + 1;

         fscanf(fptr, "%d", &n);
//         if ( (fptr = fopen(BUFFER, "w")) == NULL)
//         {
//            perror(BUFFER);
//            exit(4);
//         }
         n++;
         rewind(fptr);       
         fprintf(fptr, "%d\n", n);
         fclose(fptr);
         release.sem_num = CHILD;
         printf("A. The number [%2d] modified by parent\n", n);
         if (semop(semid, &release, 1) == -1)
         {
            perror("semop -- parent -- indicating new number has been READ");
            exit(5);
         }
         
      }
      

      
   }
   else
   {
      c_sleep = atoi(argv[1]);
      c_pid = getpid();
      for( int i = 0; i < 5; i++)
      {
         sleep(c_sleep);
         acquire.sem_num = CHILD;
         if (semop(semid, &acquire, 1) == -1)
         {
            perror("semop -- child -- waiting for new number to be READ");
            exit(7);
         }
         if ( (fptr = fopen(BUFFER, "r+")) == NULL)
         {
            perror(BUFFER);
            exit(8);
         }
        // fptr = fopen(BUFFER, "r");
         fscanf(fptr, "%d", &n);
	      n++;
 	      rewind(fptr);
	      fprintf(fptr, "%d\n", n);
         fclose(fptr);
         release.sem_num = PARENT;
         if (semop(semid, &release, 1) == -1)
         {
            perror("semop -- child -- indicating number has been WRITE");
            exit(9);
         }
         printf("B. The number [%2d] modified by child \n", n);
      }   
      sleep(5);
      printf("Semaphore removed\n");
      if (semctl(semid, 0, IPC_RMID, 0) == -1)
      {
         perror("semctl -- child");
         exit(6);
      }
   }
   exit(0);
}

