#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
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
#include "../bdd/crud.h"
#include <fcntl.h>

int afficher_script(char *buf2){
	bdd_select("SELECT script.id, script.description FROM script", buf2);
	printf("%s\n",buf2);
	return 0;
}

int choix_script(char *buf2){
	int script=0;
	afficher_script(buf2);
	printf("Quel script voulez-vous executer (Entrez l'id) ? \n");
	scanf("%d",&script);
	printf("script choisi : %d\n",script);
	return script;
}


int demander_ordre(char *buf2);


int main(int argc, char **argv){
	int ear, listener;
	char buf[BUF_SIZ];
	struct sockaddr_in sockaddr;
	socklen_t addrlen = sizeof (sockaddr);
	memset(buf,'\0',BUF_SIZ);
	int done=0;
	int ordre=0;
	int recved=0;
	if(argc!=2){
		printf("Usage : %s port_local\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	printf("Start listenConnection\n");

	listener = listenConnection(argv[1]);

	while(!done){//condition fermeture fils

		printf("End listenConnection\nStart accept\n");
		ear = accept(listener, (struct sockaddr*) &sockaddr, &addrlen);
		if(ear <0){
			printf("Can't accept\n");
			perror("accept");
			exit(EXIT_FAILURE);
		}
		if(ear ==-1){
			perror(argv[0]);
			exit(EXIT_FAILURE);
		}
		char * maj=NULL;

		while(1){
			recved=0;
			memset(buf,'\0',BUF_SIZ);
			ordre=demander_ordre(buf);
			printf("ordre = %d\n",ordre);
			sprintf(buf,"%d",ordre);
			printf("message a envoyé : %s\n",buf);
			if(sendto(ear, buf,BUF_SIZ,0, (struct sockaddr *) &sockaddr, sizeof(sockaddr))==-1){
				perror(argv[0]);
				exit(EXIT_FAILURE);
			}else{
				printf("Message envoye : %s\n",buf);
				
				bzero(buf,BUF_SIZ);
				char buffer[65535], file_buffer[65500];
				bzero(buffer,65535);
				FILE *file= NULL;
				sprintf(buffer,"resultats.txt");
				file = fopen(buffer, "wb");
				if(file){
					recved=recv(ear, file_buffer, 65500,0);
					//fwrite(file_buffer, 65500, 1, file);
					//fclose(file);

				if(recved==-1){
					perror(argv[0]);
					exit(EXIT_FAILURE);
				}else if(recved==0){
					printf("no messages are available to be received\n");}
				}else{
					fwrite(file_buffer, 65500, 1, file);
					printf("%s\n",file_buffer);
					sprintf(maj,"INSERT INTO result (idscript,result) VALUES (%d,%s)",ordre,buf);
					bdd_insert(maj);
					fclose(file);
				}
			}
		}



	}

	printf("Close open fd\n");
	close(listener);
	printf("End of server\n");
	exit(EXIT_SUCCESS);
}


int demander_ordre(char *buf2){
	int choix =0; 
	int fait=0;
	int ordre2;
	while(!fait){
		printf("Que voulez-vous faire ?\n");
		printf(" 1. Afficher les scripts disponibles\n");
		printf(" 2. Exectuter un script\n");
		printf(" Quel est votre choix (1 ou 2) ? ");
		scanf("%d",&choix);
		if(choix==1){
			system("clear");
			afficher_script(buf2);
		}
		else if(choix==2){
			system("clear");
			ordre2=choix_script(buf2);
			printf("ordre selectionné : %d\n",ordre2);
			system("clear");
			fait=1;
		}
		else{
			fait=0;
		}
	}
	return ordre2;
}

