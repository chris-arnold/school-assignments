#include "socketInclude.h"

int main (int argc, char **argv)
{
   int i, socket_fd, trace_flag = 0;
   long int pid, net_pid;
   time_t current_time;
   unsigned long int host_id;
   struct sockaddr_in server_addr;
   struct hostent *hp;
   struct in_addr client_addr;
   char host_name [256];
   current_time = time (NULL);
   pname = argv [0];

   if (argc == 2)
   {
      ;
   }
   else if (argc < 2)
   {
      printf ("argc ERROR in main: Not enough arguments");
      exit (1);
   }

/*
   Create a socket descriptor, specify the type of communication protocol
   (ie. address family and socket type).  If an error occurs, print an error
   message and quit the program.
*/

   if ((socket_fd = socket (AF_INET, SOCK_STREAM, 0)) < 0)
   {
      printf ("socket ERROR in main");
      exit (1);
   }

/*
   Establish the remote address and port number of the server.
*/

   memset (&server_addr, 0, sizeof (server_addr));
   server_addr.sin_family = AF_INET;
   hp = gethostbyname (argv [1]);
   if (hp == NULL)
   {
      printf ("gethostbyname ERROR in main: %s does not exist", argv [1]);
      exit (1);
   }
   host_id = *((unsigned long int *) (hp -> h_addr_list));
   memcpy (&server_addr.sin_addr, hp -> h_addr, hp -> h_length);
   server_addr.sin_port = htons (TCP_PORTNO);

/*
   Establish the connection between the client and server processes.  If an
   error occurs, print an error message and quit the program.
*/

   if (connect (socket_fd, (struct sockaddr *) &server_addr, sizeof (server_addr)) < 0)
   {
      printf ("connect ERROR in main");
      exit (1);
   }

/*
   Establish the local address and process id.
*/

   gethostname (host_name, sizeof (host_name));
   hp = gethostbyname (host_name);
   if (hp == NULL)
   {
      printf ("gethostbyname ERROR in main: %s does not exist", host_name);
      exit (1);
   }
   host_id = *((unsigned long int *) (hp -> h_addr_list));
   memcpy (&host_id, hp -> h_addr, sizeof (host_id));
   pid = getpid ();

/*
   Print informative message about the client.
*/

   client_addr.s_addr = host_id;
   printf ("Socket client started on %s (IP address = %s, PID = %lu) at %s", hp -> h_name, inet_ntoa (client_addr), pid, asctime (localtime (&current_time)));

/*
   Re-establish the remote address of the server.
*/

   hp = gethostbyname (argv [1]);
   host_id = *((unsigned long int *) (hp -> h_addr_list));
   memcpy (&host_id, hp -> h_addr, sizeof (host_id));
   current_time = time (NULL);

/*
   Write the process id of the client process to the message stream.  The
   process id should be the first message sent.  It is used to help the server
   identify the origin of messages when concurrent clients are sending
   messages and the trace option is enabled.  If an error occurs, print an
   error message and quit the program.

   net_pid = htonl (pid); 
   if ((i = write_n (socket_fd, (char *) &net_pid, sizeof (net_pid))) != sizeof (net_pid))
   {
      printf ("write_n ERROR in main: Process ID not sent\n");
      exit (1);
   }
*/

/*
   Send messages to the server.
*/

   send_message (stdin, socket_fd, trace_flag);

/*
   Close the connection between the client and server processes.
*/

   close (socket_fd);

/*
   Re-establish the local address.
*/

   hp = gethostbyname (host_name);
   host_id = *((unsigned long int *) (hp -> h_addr_list));
   memcpy (&host_id, hp -> h_addr, sizeof (host_id));
   current_time = time (NULL);

/*
   Print an informative message about when the client ended.
*/

   client_addr.s_addr = host_id;
   printf ("Socket client on %s (IP address = %s, PID = %lu) ended at %s", hp -> h_name, inet_ntoa (client_addr), pid, asctime (localtime (&current_time)));
   exit (0);
}

/*
   This function is used to send a message to the server.  Messages are read
   from the standard input device and sent to the server until there are no
   more messages to send.
*/

void send_message (FILE *fp, int socket_fd, int trace_flag)
{
   int i, n, message_no = 1;
   /*
   time_t current_time;
   double elapsed_time;
   time_t request_time, reply_time, net_reply_time; 
   */
   char send_line [MAX_LINE_SIZE], recv_line [MAX_LINE_SIZE];

/*
   Process messages.
*/
   char cwd[1024];
   if (getcwd(cwd, sizeof(cwd)) == NULL)
   {
      perror("getcwd() error");
      exit(4);
   }
   printf("$$ ");
   while (fgets (send_line, MAX_LINE_SIZE, fp) != NULL)
   {
      n = strlen (send_line);

/*
   Write characters to the client until there are no more to write.  If an
   error occurs during writing, print an error message.
*/

      char *temp = (char*) malloc ( n * sizeof (char *) + 1);
      char *token;

      strcpy(temp, send_line);
      token = strtok( temp, " \n");
      if( token == NULL )
         continue;
      int cmd_type = -1;
      if ( !strcmp(token, "listdir") )
      {
         cmd_type = 0;
         if ((i = write_n (socket_fd, send_line, n)) != n)
         {
            printf ("write_n ERROR in send_message");
            exit (1);
         }
         int l = read_file(fileno(stdout), socket_fd);
      }
      else if( !strcmp(token, "rmvfile") )
      {
         cmd_type = 1;
         if ((i = write_n (socket_fd, send_line, n)) != n) { printf ("write_n ERROR in send_message"); exit (1); }
         token = strtok( NULL, " \n");
         if ( token == NULL )
         {
            printf("Not enough arguements\n");
            continue;
         }

            n = read_line (socket_fd, recv_line, MAX_LINE_SIZE);
            if (n < 0)
            {
               printf ("read_line ERROR in send_message: Encoded message not received");
               exit (1);
            }
            else
            {
               fputs (recv_line, stdout);
            }
      }
      else if( !strcmp(token, "getfile") ) 
      {

         token = strtok( NULL, " \n");
         if ( token == NULL )
         {
            printf("Not enough arguements\n");
            continue;
         }
         if ((i = write_n (socket_fd, send_line, n)) != n) { printf ("write_n ERROR in send_message"); exit (1); }
         int n = read_line (socket_fd, recv_line, MAX_LINE_SIZE);
         if( strcmp(recv_line,"ERROR\n") == 0)
         {
            continue;
         }

         int fd;
         fd = open(token,O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU | S_IRGRP | S_IROTH);
         if(!fd)
         {
            printf("Failure opening file %s\n",token);
            continue;
         }
         
         if ( read_file(fd, socket_fd) != -1)
            printf("File %s recieved!\n",token);
         
         close(fd);

      }
      else if( !strcmp(token, "putfile") ) //here can check client for file existance before sending.
      {
         int n;  
         token = strtok( NULL, " \n");
         FILE *pfile;
         if ( !(pfile = fopen(token, "r")) )
         {
            printf("Error opening file %s\n", token);
            continue;
         }
         close(pfile);
         if (write_n (socket_fd, send_line, strlen(send_line)) != strlen(send_line)) { printf ("write_n ERROR in send_message"); exit (1); }
         n = read_line (socket_fd, recv_line, MAX_LINE_SIZE);
         if (n < 0)
         {
            printf ("read_line ERROR in readfile: Encoded message not received");
            exit (1);
         }
         if( strcmp(recv_line,"ERROR") == 0)
            continue;
         send_file(token, socket_fd);
      }
      else if( !strcmp(token, "exit") )   //user enters exit will properly exit client
         return;
      else
      {
         printf("Unknown input.\n");
         continue;
      }
         printf("$$ ");
   }
}
/*
   This function is used to read a message from the server, one character at
   a time, until the newline character is read.  The number of characters
   read, including the newline character, is returned to the calling function.
*/

int read_line (int fd, char *ptr, int line_size)
{
   int n, rc;
   char c;
   for (n = 1; n < line_size; n++)
   {
      if ((rc = read_n (fd, &c, 1)) == 1)
      {
	 *ptr++ = c;
	 if (c == '\n')
	 {
	    break;
         }
      }
      else if (rc == 0)
      {
	 if (n == 1)
	 {
	    return (0);
         }
	 else
	 {
	    break;
         }
      }
      else
      {
	 return (-1);
      }
   }
   *ptr = 0;
   return (n);
}

/*
   This function writes "n" characters to the server.
*/

int write_n (int fd, char *ptr, int n_bytes)
{
   int n_left, n_written;
   n_left = n_bytes;
   while (n_left > 0)
   {
      n_written = write (fd, ptr, n_left);
      if (n_written <= 0)
      {
	 return (n_written);
      }
      n_left = n_left - n_written;
      ptr = ptr + n_written;
   }
   return (n_bytes - n_left);
}

/*
   This function reads "n" characters from the server.
*/

int read_n (int fd, char *ptr, int n_bytes)
{
   int n_left, n_read;
   n_left = n_bytes;
   while (n_left > 0)
   {
      n_read = read (fd, ptr, n_left);
      if (n_read < 0)
      {
	 return (n_read);
      }
      else if (n_read == 0)
      {
	 break;
      }
      n_left = n_left - n_read;
      ptr = ptr + n_read;
   }
   return (n_bytes - n_left);
}
