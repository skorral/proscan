#define NETWORK_SUPERVISER
#define NETWORK_SUPERVISER
void finish();
void child_handler(int signum);
void daemonize( const char *lockfile );
int create_socket( char * address, int port);
int
accept_n_get_dest_IP(int sockfd, char * dest_info);
void get_dest_info(int socket, char * dest_info);
void create_directory(char * path);
void add_to_list(int client99_server00, char * dest_info);
void get_n_execute_instruction( int socket, char * dest_info
);
void refresh_list(int client99_server00);
