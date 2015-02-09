#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <syslog.h>
#include <errno.h>
#include <pwd.h>
#include <signal.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include "network_superviser.h"
#include "network_superviser.c"
/* Change this to whatever your daemon is called */
#define DAEMON_NAME "ServerDaemon"
#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1
/* P r v o i r un child handler */
/* P r v o i r une fonction deamonize */
int main( int argc, char *argv[]){
/* Initialize the logging interface */
openlog( DAEMON_NAME, LOG_PID, LOG_LOCAL5 );
syslog( LOG_INFO, "starting" );
/* deamonize this piece of code!! */
/* Daemonize */
daemonize( "/var/lock/" DAEMON_NAME );
create_directory("/etc/sss/");
/* Check the list of clients we hae */
refresh_list(99); //99 pour indiquer la liste des clients

pid_t pid = fork();
if(pid > 0){
/* The father process */
char client_info[128];
int sockfd = create_socket("localhost", 6000);
while(1){
bzero(client_info, 128);
int socket = accept_n_get_dest_IP( sockfd, client_info);
get_dest_info( socket, client_info);
add_to_list(99, client_info);
close(socket);
sleep(15);
refresh_list(99);
}
} else if(pid == 0){
/* The child process */
int sockfd = create_socket("localhost", 6001);
int socket;
char client_info[128];

while(1){
if((socket = accept_n_get_dest_IP( sockfd,
client_info))){
pid_t pid1 = fork();
if(pid1 == 0){
/* child process */
get_n_execute_instruction(socket, client_info);
exit(EXIT_SUCCESS);
}
close(socket);
}else{
/* logguer erreur PID... */
syslog( LOG_ERR, "Error while forking." );
exit(EXIT_FAILURE);
}
}
}
return 0;
}
