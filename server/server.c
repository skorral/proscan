#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <errno.h>
#include "../common/net.h"
#include "../common/const.h"
#include <unistd.h>


int main(int argc, char **argv){
	int ear, listener;
	char buf[BUF_SIZ];
	struct sockaddr_in sockaddr;
	ssize_t written=0;
	socklen_t addrlen = sizeof (sockaddr);
	memset(buf,'\0',BUF_SIZ);
	pid_t childpid;
	pid_t pid=getpid();
	if(argc!=2){
		printf("Usage : %s port_local\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	printf("[%d] start listenConnection\n",pid);
	listener = listenConnection(argv[1]);
	while(1){

		printf("[%d] end listenConnection\nstart accept\n",pid);
		ear = accept(listener, (struct sockaddr*) &sockaddr, &addrlen);
		if(ear <0){
			printf("[%d] can't accept\n",pid);
			perror("accept");
			exit(EXIT_FAILURE);
		}
		if(ear ==-1){
			perror(argv[0]);
			exit(EXIT_FAILURE);
		}
		printf("[%d] End accept\n",pid);
		if((childpid = fork()) == 0) {

			sprintf(buf,"[%d] Début d'échange de commande\n",pid);
			printf("[%d] buffer = %s\n",pid,buf);
			printf("[%d] Début du test de write\n",pid);

			if((written = sendto(ear, buf, BUF_SIZ,0, (struct sockaddr *) &sockaddr, sizeof(sockaddr)))==-1){
				perror("problem with Written");
				return errno;
			}
			printf("[%d] Fin du test du write\n",pid);
			while(1){
				scanf("%s",buf);
				written = sendto(ear, buf,BUF_SIZ,0, (struct sockaddr *) &sockaddr, sizeof(sockaddr));
				printf("[%d] message envoye : %s\n",pid,buf);
			}
			printf("[%d] close sockaddr\n",pid);
		}
		else if ((childpid != 0)){
			printf("[%d] have fork, the child is [%d]\n",pid,childpid);
		}
		else if (childpid == -1) {
			perror("Le fork n'a pas fonctionné");
			exit(EXIT_FAILURE); // quitte le programme si le fork n'as pas fonctionné
		}

	}
	printf("[%d] Close open fd\n",pid);
	close(ear);
	close(listener);
	printf("[%d] End of server\n",pid);
	exit(EXIT_SUCCESS);
}

