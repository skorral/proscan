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



int main(int argc, char **argv){
	int ear, listener;
	char buf[BUF_SIZ];
	struct sockaddr_in sockaddr;
	ssize_t written=0;
	socklen_t addrlen = sizeof (sockaddr);
	memset(buf,'\0',BUF_SIZ);
	pid_t childpid;
	if(argc!=2){
		printf("Usage : %s port_local\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	printf("start listenConnection\n");
	listener = listenConnection(argv[1]);
	while(1){

		printf("end listenConnection\nstart accept\n");
		ear = accept(listener, (struct sockaddr*) &sockaddr, &addrlen);
		if(ear <0){
			printf("can't accept\n");
			perror("accept");
			exit(EXIT_FAILURE);
		}
		if(ear ==-1){
			perror(argv[0]);
			exit(EXIT_FAILURE);
		}
		printf("End accept\n");
		if((childpid = fork()) == 0) {

			sprintf(buf,"Début d'échange de commande\n");
			printf("buffer = %s\n",buf);
			printf("Début du test de write\n");

			if((written = sendto(ear, buf, BUF_SIZ,0, (struct sockaddr *) &sockaddr, sizeof(sockaddr)))==-1){
				perror("problem with Written");
				return errno;
			}
			printf("Fin du test du write\n");
			while(1){
				scanf("%s",buf);
				written = sendto(ear, buf,BUF_SIZ,0, (struct sockaddr *) &sockaddr, sizeof(sockaddr));
				printf("message de %s envoye\n",buf);
			}
			printf("close sockaddr\n");
		}
	}
	printf("Close open fd\n");
	close(ear);
	close(listener);
	printf("End of server\n");
	exit(EXIT_SUCCESS);
}

