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
#include <fnctl.h>


void removefifo(void){
	        unlink(pipeperso)
}

void afficher_script(void){
	bdd_select("SELECT script.id script.nom, script.description FROM script");
	exit(EXIT_SUCCESS);
}

void afficher_client(void){
	bdd_select("SELECT client.id client.hostname, client.ip FROM client WHERE client.connected=1");
	exit(EXIT_SUCCESS);
}

int choix_script(){
	int script=0;
	afficher_script();
	printf("Quel script voulez-vous executer (Entrez l'id) ? \n");
	scanf("%d",&script);
	return script;
}

int choix_client(){
	int client=0;
	printf("Sur quel client (Entrez l'id) ? \n");
	scanf("%d",&client);
	return client;
}

int demander_ordre(int ordre[2]){
	int choix =0;
	int fait=0;
	FIlE *common;
	while(!fait){
		printf("Que voulez-vous faire ?\n");
		printf(" 1. Afficher les scripts disponibles\n");
		printf(" 2. Afficher les clients connectés\n");
		printf(" 3. Exectuter un script\n");
		printf(" Quel est votre choix (1, 2 ou 3) ? ");
		scanf("%d",&choix);
		if(choix==1){
			afficher_script();
		}
		else if(choix==2){
			afficher_client();
		}
		else if(choix==3){
			ordre[0]=choix_script();
			ordre[1]=choix_client();
		}
		fait=1;
	}
	common=open(pipeperso, O_WRONLY);
	write(common,ordre[0],strlen(ordre[0]);
	write(common,ordre[1],strlen(ordre[1]);
	close(common);
	exit(EXIT_SUCCESS);
}


int main(int argc, char **argv){
	int ear, listener;
	char buf[BUF_SIZ];
	struct sockaddr_in sockaddr;
	socklen_t addrlen = sizeof (sockaddr);
	memset(buf,'\0',BUF_SIZ);
	pid_t childpid;
	pid_t pid=getpid();
	int done=0;
	        if(mkfifo(pipeperso, S_IRUSR | S_IWRITE | S_IWGRP)==-1 && erno != EEXIST){
			                printf("Cannot make pipe\n"); 
					        }
		if(atexit(removefifo)!= 0)
		                printf("Error in removing fifo\n");
	if(mkfifo(pipe_serv, S_IRUSR | S_IWRITE | S_IWGRP)==-1 && erno != EEXIST){
		printf("Cannot make pipe\n");
	}
	if(atexit(removefifo)!= 0)  printf("Error in removing fifo\n");
	int ordre[2];
	if(argc!=2){
		printf("Usage : %s port_local\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	printf("[%d] start listenConnection\n",pid);
	listener = listenConnection(argv[1]);

	while(!done){//condition fermeture fils

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
			int end=0;
			FILE *common;
			int mypid=getpid();
			char *rip=NULL;
			char *rhostname=NULL;
			char *idclient;
			int todo[2];
			char * maj ="INSERT INTO client (ip,hostname, pid, connecte    d) VALUES (";
			char *maj2="INSERT INTO result (idclient,id    script,result) VALUES ("
			sendto(ear, "ip",sizeof("ip"),0, (struct sockaddr *) &sockaddr, sizeof(sockaddr));
			recvfrom(ear,rip, sizeof(rip), 0 ,NULL, NULL);
			sendto(ear, "hostname",sizeof("hostname"),0, (struct sockaddr *) &sockaddr, sizeof(sockaddr));
			recvfrom(ear,rhostname, sizeof(rhostname), 0 ,NULL, NULL);
			strcat(maj,",");
			strcat(maj,rip);
			strcat(maj,",");
			strcat(maj,rhostname);
			strcat(maj,",");
			strcat(maj,mypid);
			strcat(maj,"1");
			strcat(maj,")");
			bdd_insert(maj);
		

			sprintf(buf,"[%d] Début d'échange de commande\n",pid);
				if(mkfifo(pipeperso, S_IRUSR | S_IWRITE | S_IWGRP)==-1 && erno != EEXIST){
					                printf("Cannot make pipe\n"); 
							        }
			while(!end){
				common=open(pipeperso, O_RDONLY);
				read(common,todo[0],strlen(buf));
				read(common,todo[1],strlen(buf));
				if(strcmp(todo[1],"quit")){
					end=1;
				}
				else{
					sendto(ear, buf,BUF_SIZ,0, (struct sockaddr *) &sockaddr, sizeof(sockaddr));
					printf("[%d] message envoye : %s\n",pid,buf);
					recvfrom(ear, buf,BUF_SIZ,0,NULL,NULL);
				
					maj="INSERT INTO result (idclient,i    dscript,result) VALUES ()";
					strcat(maj,todo[1]);
					strcat(maj,",");
					strcat(maj,todo[0]);
					strcat(maj,",");
					strcat(maj,buf);
					bdd_insert(maj);
				}
			}
			printf("[%d] close sockaddr\n",pid);
			close(ear);
			done=1;
		}
		else if ((childpid != 0)){//pere
			close(tun_serv[1]);
			printf("[%d] have fork, the child is [%d]\n",pid,childpid);
			demander_ordre(ordre);


			close(ear);
		}
		else if (childpid == -1) {
			perror("Le fork n'a pas fonctionné");
			exit(EXIT_FAILURE); // quitte le programme si le fork n'as pas fonctionné
		}

	}
	printf("[%d] Close open fd\n",pid);
	close(listener);
	printf("[%d] End of server\n",pid);
	exit(EXIT_SUCCESS);
}

