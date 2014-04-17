#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/file.h>
#include <dirent.h>

#define TCP_PORTNO 4259
#define MAX_LINE_SIZE 255 

char *pname;

void send_message (FILE *fp, int socket_fd, int trace_flag);
int read_line (int fd, char *ptr, int line_size);
int write_n (int fd, char *ptr, int n_bytes);
int read_n (int fd, char *ptr, int n_bytes);
void message_echo (int socket_fd);
void display_error (int error_code);

int send_file(char *filename, int socket_fd)
{
   FILE *fp;
   fp = fopen(filename,"r");
   struct stat buf;
   int i, filesize;
   char size[1024];
   if(!fp)
   {
      int i;
      printf("Failure opening file %s\n",filename);
      if((i = write_n(socket_fd, "ERROR\n", 6)) != 6)
      {
          printf ("write_n ERROR in send_file error");
          exit (1);
      }
      return -1;
   }
   else
   {
   		if((i = write_n(socket_fd, "SUCCESS\n", 8)) != 8)
   		{
	       printf ("write_n ERROR in send_file success");
	       exit (1);
	   }
   }
   stat(filename,&buf);
   filesize = buf.st_size;
   sprintf(size,"%d\n",filesize);
   int q = strlen(size);
   if((i = write_n(socket_fd, size, q) != q))
   {
       printf ("write_n ERROR in send_file size");
       exit (1);
   }

   char file_array[q];
   int sent, total=0;
   printf("Sending file....");
   fflush(stdout);
   while((sent = fread(file_array, sizeof(char), q, fp)) > 0)
   {
      total += sent;
      if(send(socket_fd, file_array,sent, 0) < 0)
      {
         printf("fail to send file.\n");
         exit(2);
      }
   }
   printf(" File transfer complete. %d bytes were sent.\n",total);

   close(fp);
}

int read_file(int fd, int socket_fd)
{
   char recv_line [MAX_LINE_SIZE];
   char size[1024];
   int n;
   n = read_line (socket_fd, recv_line, MAX_LINE_SIZE);
   if (n < 0)
   {
      printf ("read_line ERROR in readfile: Encoded message not received");
      exit (1);
   }
   if( strcmp(recv_line,"ERROR\n") == 0)
      return -1;

   n = read_line (socket_fd, size, MAX_LINE_SIZE);
   if (n < 0)
   {
      printf ("read_line ERROR in readfile: Encoded message not received");
      exit (1);
   }
   int isize = atoi(size);
   char file_array[isize];
   int bytes_recieved=0,total=0;
   while(total != isize)
   {
      bytes_recieved = read(socket_fd,file_array,isize);
      write(fd,file_array,bytes_recieved);
      total += bytes_recieved;
   }
}
