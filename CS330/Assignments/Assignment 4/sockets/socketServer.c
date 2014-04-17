#include "socketInclude.h"

int main (int argc, char **argv)
{
   int socket_fd, new_socket_fd, addr_length, child_pid;
   unsigned long int host_id;
   struct sockaddr_in client_addr, server_addr;
   struct hostent *hp;
   char host_name [256];
   pname = argv [0];
   if ((socket_fd = socket (AF_INET, SOCK_STREAM, 0)) < 0)
   {
      printf ("socket ERROR in main");
      exit (1);
   }
   else
   {
      memset (&server_addr, 0, sizeof (server_addr));
      server_addr.sin_family = AF_INET;
      gethostname (host_name, sizeof (host_name));
      hp = gethostbyname (host_name);
      if (hp == NULL)
      {
	 printf ("gethostbyname ERROR in main: %s does not exist", host_name);
	 exit (1);
      }
      else
      {
	 host_id = *((unsigned long int *) (hp -> h_addr_list));
         memcpy (&server_addr.sin_addr, hp -> h_addr, hp -> h_length);
         server_addr.sin_port = htons (TCP_PORTNO);
         if (bind (socket_fd, (struct sockaddr *) &server_addr, sizeof (server_addr)) < 0)
	 {
	    printf ("bind ERROR in main");
	    exit (1);
         }
	 else
	 {
	    addr_length = sizeof (server_addr);
	    if (getsockname (socket_fd, (struct sockaddr *) &server_addr, &addr_length) < 0)            {
	       printf ("getsockname ERROR in main");
	       exit (1);
            }
	    else
	    {
	       printf ("Parent: Server on port %d\n", ntohs (server_addr.sin_port));
	       if (listen (socket_fd, 5) < 0)
	       {
		  printf ("listen ERROR in main");
		  exit (1);
               }
	       else
	       {
		  for ( ; ; )
		  {
		     printf ("Parent: Waiting for client\n");
		     addr_length = sizeof (client_addr);
		     new_socket_fd = accept (socket_fd, (struct sockaddr *) &client_addr, &addr_length);
		     printf ("Parent: Client arrived\n");
		     if (new_socket_fd < 0)
		     {
			printf ("accept ERROR in main");
			exit (1);
                     }
		     else
		     {
			if ((child_pid = fork ()) < 0)
			{
			   printf ("child fork ERROR in main");
			   exit (1);
                        }
			else if (child_pid == 0)
			{
			   printf ("Child: Fork OK\n");
			   close (socket_fd);
			   message_echo (new_socket_fd);
			   printf ("Child: Done\n");
			   exit (0);
                        }
			else
			{
			   close (new_socket_fd);
                        }
                     }
                  }
               }
            }
         }
      }
   }
}

void message_echo (int socket_fd)
{
   int i, n;
   char line [MAX_LINE_SIZE];
   char cwd[1024];
   if (getcwd(cwd, sizeof(cwd)) == sizeof(cwd))
   {
      perror("getcwd() error");
      exit(4);
   }

   for ( ; ; )
   {
      n = read_line (socket_fd, line, MAX_LINE_SIZE);
      if (n == 0)
      {  
	 break;
      }
      else if (n < 0)
      {
	 printf ("read_line ERROR in message_echo");
	 exit (1);
      }
      char *temp = (char*) malloc ( n * sizeof (char *) + 1);
      char *token;
      memcpy(temp, line, n);
      token = strtok( temp, " \n");
      if ( !strcmp(token, "listdir") )
      {
         printf("Command listdir recieved.\n");
         if( write_n (socket_fd, "Roger that Client. Ready to issue command LISTDIR.\n", 51) != 51 )
         {
            printf ("write_n ERROR in message_echo");
            exit (1);
         }
      }
      else if( !strcmp(token, "rmvfile") )
      {
         token = strtok( NULL, " \n");
         printf("Request recieved to remove %s\n", token);
         if( write_n (socket_fd, "Roger that Client. Ready to issue command rmvfile.\n", 51) != 51 )
         {
            printf ("write_n ERROR in message_echo");
            exit (1);
         }
      }
      else if( !strcmp(token, "getfile") ) //here can check client for file existance before sending.
      {
         token = strtok( NULL, " \n");
         printf("Request to send %s recieved.\n", token);
         if( write_n (socket_fd, "Roger that Client. Ready to issue command getfile.\n", 51) != 51 )
         {
            printf ("write_n ERROR in message_echo");
            exit (1);
         }
      }
      else if( !strcmp(token, "putfile") )
      {
         token = strtok( NULL, " \n");
         printf("Request to create %s recieved.\n", token);
         if( write_n (socket_fd, "Roger that Client. Ready to issue command putfile.\n", 51) != 51 )
         {
            printf ("write_n ERROR in message_echo");
            exit (1);
         }
      }
      else
       { 
         {
            printf ("Unknown Command");
            return;
         }
      }
      /*
      for (i = 0; i < n; i ++)
      {
	  printf ("%c", line [i]);
      }
      if (write_n (socket_fd, line, n) != n)
      {
         printf ("write_n ERROR in message_echo");
	 exit (1);
      }
      */
   }
}

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
