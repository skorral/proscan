#include<stdio.h>

#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<syslog.h>
#include<errno.h>
#include<pwd.h>
#include<signal.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<netdb.h>
#include<time.h>
#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1
/* Change this to the user under which to run */
#define RUN_AS_USER "af"
void finish(){
syslog( LOG_NOTICE, "terminated" );
closelog();
}
void child_handler(int signum)
{
switch(signum) {
case SIGALRM: exit(EXIT_FAILURE); break;
case SIGUSR1: exit(EXIT_SUCCESS); break;
case SIGCHLD: exit(EXIT_FAILURE); break;
case SIGTERM: finish(); exit(EXIT_SUCCESS); break;
}
}
void daemonize( const char *lockfile )
{
pid_t pid, sid, parent;
int lfp = -1;
/* already a daemon */
if ( getppid() == 1 ) return;

/* Create the lock file as the current user */
if ( lockfile && lockfile[0] ) {
lfp = open(lockfile,O_RDWR|O_CREAT,0640);
if ( lfp < 0 ) {
syslog( LOG_ERR, "unable to create lock file %s, code=%d (%s)",lockfile, errno, strerror(errno) );
exit(EXIT_FAILURE);
}
}
/* Drop user if there is one, and we were run as root */
if ( getuid() == 0 || geteuid() == 0 ) {
struct passwd *pw = getpwnam(RUN_AS_USER);
if ( pw ) {
syslog( LOG_NOTICE, "setting user to " RUN_AS_USER );
setuid( pw->pw_uid );
}
}
/* Trap signals that we expect to recieve */
signal(SIGCHLD,child_handler);
signal(SIGUSR1,child_handler);
signal(SIGALRM,child_handler);
signal(SIGTERM,child_handler);
/* Fork off the parent process */
pid = fork();


if (pid < 0) {
syslog( LOG_ERR, "unable to fork daemon, code=%d (%s)",errno, strerror(errno) );
exit(EXIT_FAILURE);
}
/* If we got a good PID, then we can exit the parent
process. */
if (pid > 0) {
/* Wait for confirmation from the child via SIGTERM or
SIGCHLD, or
for two seconds to elapse (SIGALRM). pause() should
not return. */
alarm(2);
pause();
exit(EXIT_FAILURE);
}
/* At this point we are executing as the child process */

parent = getppid();
/* Cancel certain signals */
signal(SIGCHLD,SIG_DFL); /* A child process dies */
signal(SIGTSTP,SIG_IGN); /* Various TTY signals */
signal(SIGTTOU,SIG_IGN);
signal(SIGTTIN,SIG_IGN);
signal(SIGHUP, SIG_IGN); /* Ignore hangup signal */
//signal(SIGTERM,SIG_DFL); /* Die on SIGTERM */
/* Change the file mode mask */
umask(0);
/* Create a new SID for the child process */
sid = setsid();
if (sid < 0) {
syslog( LOG_ERR, "unable to create a new session, code%d (%s)",errno, strerror(errno) );
exit(EXIT_FAILURE);
}
/* Change the current working directory. This prevents
the current
directory from being locked; hence not being able to
remove it. */
if ((chdir("/")) < 0) {
syslog( LOG_ERR, "unable to change directory to %s,code %d (%s)","/", errno, strerror(errno) );
exit(EXIT_FAILURE);

}
/* Redirect standard files to /dev/null */
freopen( "/dev/null", "r", stdin);
freopen( "/dev/null", "w", stdout);
freopen( "/dev/null", "w", stderr);
/* Tell the parent process that we are A-okay */
kill( parent, SIGUSR1 );
}
 int create_socket( char * address, int port){
int sockfd;
struct sockaddr_in serv_addr;
sockfd = socket(AF_INET, SOCK_STREAM, 0);
if (sockfd < 0){
syslog( LOG_ERR, "Unable to opening socket, code %d (%s)", errno, strerror(errno) );
exit(EXIT_FAILURE);
}
bzero((char *) &serv_addr, sizeof(serv_addr));
serv_addr.sin_family = AF_INET;
serv_addr.sin_port = htons(port);
if(strcmp(address, "localhost") == 0){
serv_addr.sin_addr.s_addr = INADDR_ANY;
if (bind(sockfd, (struct sockaddr *) &serv_addr,sizeof(
serv_addr)) < 0){
syslog( LOG_ERR, "Error on biding, code %d (%s)",errno, strerror(errno) );
exit(EXIT_FAILURE);
}
listen(sockfd,5);
syslog( LOG_INFO, "Socket on local:%d is now listening", port);
}else{
struct hostent *server;
server = gethostbyname(address);
if(server == NULL){
syslog( LOG_ERR, "Cannot find the host ’%s’, code %d(%s)",address, errno, strerror(errno) );
sockfd = -1;
return sockfd;
}
bcopy((char *)server->h_addr,(char *)&serv_addr.sin_addr.s_addr, server->h_length);
if(connect(sockfd, (struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0){
syslog( LOG_ERR, "Cannot connect to the host ’%s:%d’,code %d (%s)",address,port, errno, strerror(errno) );
sockfd = -1;
return sockfd;
}
}
return sockfd;
}
 int accept_n_get_dest_IP(int sockfd, char * dest_info){
int newsockfd;
socklen_t clilen;
struct sockaddr_in cli_addr;
clilen = sizeof(cli_addr);
syslog(LOG_INFO,"Waiting for a connection...");
newsockfd = accept(sockfd,
(struct sockaddr *) &cli_addr, &clilen);
sprintf(dest_info, "%s", inet_ntoa(cli_addr.sin_addr));
syslog(LOG_INFO,"Accepted connection from %s", dest_info);
if(newsockfd < 0){
syslog( LOG_ERR, "Error on accept, code %d (%s)", errno, strerror(errno) );
exit(EXIT_FAILURE);
}
return newsockfd;
}
 void get_dest_info(int socket, char * dest_info){


int n;
char buffer1[96], buffer2[32], local_hostname[64];
bzero(buffer1, 96); bzero(buffer2, 32); bzero(
local_hostname, 64);
n = read(socket, buffer1, 96);
if (n < 0){
syslog( LOG_ERR, "Error reading from socket, code %d (%s)", errno, strerror(errno) );
close(socket);
exit(EXIT_FAILURE);
}
strcpy(buffer2, dest_info);
bzero(dest_info, 128);
sprintf(dest_info, "1 %s %s \n", buffer2, buffer1);
gethostname(local_hostname, 64);
n = write(socket, local_hostname, 64);
if (n < 0){
syslog( LOG_ERR, "Error writing socket, code %d (%s)",errno, strerror(errno) );
close(socket);
exit(EXIT_FAILURE);
}
return;}
 void create_directory(char * path){
int status;
status = mkdir(path, S_IRWXU | S_IRWXG | S_IROTH |S_IXOTH);//rwx for u-g rx for oth
if(status < 0){
if(errno == EEXIST) {
syslog( LOG_INFO, "The directory ’%s’ already exists", path);
}else{
syslog( LOG_INFO, "Unable to create the directory ’%s’, code %d (%s)", path, errno, strerror(errno));
exit(EXIT_FAILURE);
}
}else{
syslog( LOG_INFO, "The directory ’%s’ is created", path);
}
return;
}
 void add_to_list(int client99_server00, char * dest_info){
char buffer[80];
char ip_read[16], ip_received[16];
char hostname_read[64], hostname_received[64];
char version_read[6], version_received[6];
int exists = 0, n_received, n_read;
char path[256];
FILE *file = NULL;
sscanf(dest_info, "%d %s %s %s ", &n_received, ip_received, hostname_received, version_received);
if(client99_server00 == 99){
file = fopen("/etc/sss/ClientsList.txt", "r");
}else{
file = fopen("/etc/ssa/server.txt","r");
}
if(file){
while(fgets(buffer, 80, file) != NULL){
sscanf(buffer, "%d %s %s %s ", &n_read, ip_read,hostname_read, version_read);
if((strcmp(ip_read, ip_received) == 0) && (strcmp(hostname_received, hostname_read) == 0)) {
if(n_read == 1){
exists = 1;
break;
}
}
}
fclose(file);
}else if(errno == ENOENT){
//Ce test est vide, ce n’est pas un oubli. Il s’agit d’exclure ce cas d’erreurs.
}else{
syslog( LOG_ERR, "Unable to open the list, code %d (%s)", errno, strerror(errno) );
exit(EXIT_FAILURE);
}
if(exists == 0){
FILE *file = NULL;
if(client99_server00 == 99){
file = fopen("/etc/sss/ClientsList.txt", "a");
if(n_received == 1){
bzero(path, 256);
sprintf(path, "/etc/sss/%s", ip_received);
create_directory(path);
}
}else{
file = fopen("/etc/ssa/server.txt","a");
}
if(file){
fwrite(dest_info, 1, strlen(dest_info),file);
fclose(file);
syslog( LOG_INFO, "%s %s has been added to the list", hostname_received, ip_received);
}else{
syslog( LOG_ERR, "Unable to open the list, code %d(%s)", errno, strerror(errno) );
exit(EXIT_FAILURE);
}
}
return;
}
void refresh_list(int client99_server00){
FILE *file = NULL;
int port_num;
char buffer[192], buffer_file[80], buffer_socket[128],hostname_dest[64], ip[16],local_hostname[64], version[6];
int inscrit, n, sockfd;
bzero(local_hostname, 64);
gethostname(local_hostname, 64);
if( client99_server00 == 99){
rename("/etc/sss/ClientsList.txt", "/etc/sss/ClientsList_old.txt");
file = fopen("/etc/sss/ClientsList_old.txt", "r");
port_num = 7000;
}else{
rename("/etc/ssa/server.txt", "/etc/ssa/server_old.txt");
file = fopen("/etc/ssa/server_old.txt", "r");
port_num = 6000;
}
if(file){
while(fgets(buffer_file, 80, file) != NULL){
bzero(ip, 16);
bzero(version, 6);
bzero(hostname_dest, 64);
sscanf(buffer_file,"%d %s %s %s ", &inscrit, ip,hostname_dest, version);
if(inscrit == 0){
sockfd = create_socket(ip, port_num);
if(sockfd == -1){
syslog(LOG_INFO, "The host %s is not up, it wasnot subscribed.", ip);
add_to_list(client99_server00, buffer_file);
bzero(buffer_file, 80);
continue;
}
n = write(sockfd, local_hostname, sizeof(local_hostname));
if (n < 0) {
syslog( LOG_ERR, "ERROR sending hostname to %s,code %d (%s)", ip, errno, strerror(errno) );
close(sockfd);
exit(EXIT_FAILURE);
}
bzero(buffer_socket, 128);
n = read(sockfd, buffer_socket, 127);
if (n < 0){
syslog( LOG_ERR, "Error reading from socket,code %d (%s)", errno, strerror(errno) );
close(sockfd);
exit(EXIT_FAILURE);
}
bzero(buffer, 192);
sprintf(buffer, "1 %s %s \n", ip, buffer_socket);
add_to_list(client99_server00, buffer);
}else if(inscrit == 1){
add_to_list(client99_server00, buffer_file);
}else{
syslog( LOG_ERR, "Error on the first column in the list (only values 1/0 for subscribed/not subscribed are accepted)" );
close(sockfd);
exit(EXIT_FAILURE);
}
bzero(buffer_file, 80);
}
fclose(file);
if( client99_server00 == 99){
remove("/etc/sss/ClientsList_old.txt");
}else{
remove("/etc/ssa/server_old.txt");
}
}else{
syslog( LOG_INFO, "No list found, it will be created..." );
FILE *file = NULL;
if(client99_server00 == 99){
file = fopen("/etc/sss/ClientsList.txt", "w");
fclose(file);
}else{
file = fopen("/etc/ssa/server.txt","w");
fclose(file);
}
}
}
void get_n_execute_instruction( int socket, char* dest_info){
int n, num_script;
char buffer[65535], instruction[9], ip[16];
bzero(buffer, 65535);
bzero(instruction, 9);
bzero(ip, 16);
n = read(socket,buffer,65535);
if (n < 0){
syslog( LOG_ERR, "Error reading instruction from socket, code %d (%s)",errno, strerror(
errno) );
close(socket);
exit(EXIT_FAILURE);
}
sscanf(buffer, "%s %s %d ", instruction, ip, &num_script);
bzero(buffer, 65535);
if(!strcmp(instruction,"QUERY")){
/* envoie de r e q u t e au client */
int newsocket = create_socket( ip, 7001);
sprintf(buffer, "EXECUTE %s %d ", ip,num_script);
n = write(newsocket, buffer, strlen(buffer));
if (n < 0){
syslog( LOG_ERR, "Error sending instructionto ’%s:7001’, code %d (%s)", ip,errno,strerror(errno) );
close(newsocket);
exit(EXIT_FAILURE);
}
close(newsocket);
}else if(!strcmp(instruction, "RESPONSE")){
/* reception de r s u l t a t s */
char file_buffer[65500];
char file_name[100];
int file_size;
bzero(file_buffer, 65500);
bzero(buffer, 65535);
n = read(socket,buffer,65535);
if (n < 0){
syslog( LOG_ERR, "Error receiving the response size, code %d (%s)",errno,strerror(errno) );
close(socket);
exit(EXIT_FAILURE);
}
sscanf(buffer, "%d %s ", &file_size,file_name);
const char s[4]="@@@";
char *token;
token = strtok(buffer, s);
bzero(file_buffer, 65500);
sprintf(file_buffer, "%s ", token);
token = strtok(NULL, s);
bzero(file_buffer, 65500);
sprintf(file_buffer, "%s ", token);
bzero(buffer, 65535);
sprintf(buffer, "/etc/sss/%s/%s", ip,file_name);

FILE *file = NULL;
file = fopen(buffer, "wb");
if(file){
fwrite(file_buffer, 1, file_size, file);
fclose(file);
syslog( LOG_INFO, "Result file is successfully saved");
}else{
syslog( LOG_ERR, "Unable to create %s ,code %d (%s)", buffer, errno, strerror(errno) );
exit(EXIT_FAILURE);
}
}else if(!strcmp(instruction, "EXECUTE")) {
FILE* result_file;
char * file_buffer;
char file_name[100], script_path[256],result_path[256], command[512], buffer[65535];
int sockfd, n;
time_t t = time(NULL);
struct stat s;
bzero(file_name, 100);
bzero(script_path, 256);
bzero(result_path, 256);
bzero(command, 512);
bzero(buffer, 65535);
//sprintf(file_name, "result_%d_%s.txt",
num_script, ctime(&t);
sprintf(file_name, "result_%d.txt",num_script);
sprintf(script_path, "/etc/ssa/scripts/script_%d.sh", num_script);
sprintf(result_path, "/etc/ssa/results/%s",file_name);
sprintf(command, "/bin/bash %s > %s",script_path, result_path);
sockfd = create_socket( dest_info, 6001);
system(command);
stat(result_path, &s);
file_buffer = (char *)malloc(s.st_size);
result_file = fopen(result_path, "rb");
if(result_file){
n = fread(file_buffer, 1, s.st_size,result_file);

if(n<=0){
n=1;
syslog( LOG_ERR, "Error reading the scan result_file, code %d (%s)", errno,strerror(errno) );
sprintf(buffer, "RESPONSE %s %d ", ip,num_script);
n = write(sockfd, buffer, strlen(buffer));
if (n < 0){
syslog( LOG_ERR, "Error writing tosocket, code %d (%s)", errno,strerror(errno) );
close(sockfd);
exit(EXIT_FAILURE);
}
bzero(buffer, 65535);
sprintf(buffer, "78 %s @@@Error reading the scan results file! check the script number...@@@ ", file_name);
sleep(1);
n = write(sockfd, buffer, strlen(buffer));
if (n < 0){
syslog( LOG_ERR, "Error writing to socket, code %d (%s)", errno,strerror(errno) );
close(sockfd);
exit(EXIT_FAILURE);
}
close(sockfd);
exit(EXIT_FAILURE);
}
sprintf(buffer, "RESPONSE %s %d ", ip,num_script);
n = write(sockfd, buffer, strlen(buffer));
if (n < 0){
syslog( LOG_ERR, "Error sending result to server, code %d (%s)", errno,strerror(errno) );
fclose(result_file);
close(sockfd);
exit(EXIT_FAILURE);
}
bzero(buffer, 65535);
sprintf(buffer, "%d %s @@@%s@@@ ", (int)s.st_size, file_name, file_buffer);
sleep(1);

n = write(sockfd, buffer, strlen(buffer));
if (n < 0){
syslog( LOG_ERR, "Error sending resultfile name and size to server, code %d(%s)", errno, strerror(errno) );
fclose(result_file);
close(sockfd);
exit(EXIT_FAILURE);
}
fclose(result_file);
close(sockfd);
}else{
syslog( LOG_ERR, "Error reading the scanresult_file, code %d (%s)", errno,strerror(errno) );
sprintf(buffer, "RESPONSE %s %d", ip,num_script);
n = write(sockfd, buffer, strlen(buffer));
if (n < 0){
syslog( LOG_ERR, "Error writing to socket, code %d (%s)", errno, strerror(errno) );
close(sockfd);
exit(EXIT_FAILURE);
}
bzero(buffer, 65535);
sprintf(buffer, "48 %s", file_name);
n = write(sockfd, buffer, strlen(buffer));
if (n < 0){
syslog( LOG_ERR, "Error writing to socket, code %d (%s)", errno, strerror(errno) );
close(sockfd);
exit(EXIT_FAILURE);
}
bzero(buffer, 65353);
sprintf(buffer, "Error reading the scan results file!");
n = write(sockfd, buffer, strlen(buffer));
if (n < 0){
syslog( LOG_ERR, "Error writing to socket, code %d (%s)", errno, strerror(errno) );
close(sockfd);
exit(EXIT_FAILURE);
}
close(sockfd);
exit(EXIT_FAILURE);
}
}else{
/* Logguer r e q u t e non reconnue */
syslog( LOG_ERR, "Unknown instruction ’%s’", instruction);
exit(EXIT_FAILURE);
}
return;
}
