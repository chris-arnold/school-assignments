#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/file.h>

#define TCP_PORTNO 4259
#define MAX_LINE_SIZE 255 

char *pname;

void send_message (FILE *fp, int socket_fd, int trace_flag);
int read_line (int fd, char *ptr, int line_size);
int write_n (int fd, char *ptr, int n_bytes);
int read_n (int fd, char *ptr, int n_bytes);
void message_echo (int socket_fd);
void display_error (int error_code);
