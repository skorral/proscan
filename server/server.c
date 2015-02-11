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


void afficher_script(char *buf2){
	bdd_select("SELECT script.id script.nom, script.description FROM script", buf2);
	printf("%s\n",buf2);
	exit(EXIT_SUCCESS);
}

void afficher_client(char *buf2){
	bdd_select("SELECT client.id client.hostname, client.ip FROM client WHERE client.connected=1",buf2);
	printf("%s\n",buf2);
	exit(EXIT_SUCCESS);
}

int choix_script(char *buf2){
	int script=0;
	afficher_script(buf2);
	printf("Quel script voulez-vous executer (Entrez l'id) ? \n");
	scanf("%d",&script);
	return script;
}

int choix_client(char *buf2){
	int client=0;
	afficher_client(buf2);
	printf("Sur quel client (Entrez l'id) ? \n");
	scanf("%d",&client);
	return client;
}

int demander_ordre(int ordre[2], char *buf2);

int main(int argc, char **argv){
	int ear, listener;
	char buf[BUF_SIZ];
	char buf2[BUF_SIZ];
	struct sockaddr_in sockaddr;
	socklen_t addrlen = sizeof (sockaddr);
	memset(buf,'\0',BUF_SIZ);
	pid_t childpid;
	pid_t pid=getpid();
	int done=0;
	char *pipeperso=NULL;
	char *pipe_serv=NULL;
	if(mkfifo(pipeperso, S_IRUSR | S_IWRITE | S_IWGRP)==-1 && errno != EEXIST){
		printf("Cannot make pipe\n"); 
	}
	if(mkfifo(pipe_serv, S_IRUSR | S_IWRITE | S_IWGRP)==-1 && errno != EEXIST){
		printf("Cannot make pipe\n");
	}
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
			int common;
			int mypid=getpid();
			char *rip=NULL;
			char *rhostname=NULL;
			//char *idclient;
			int todo[2];
			char * maj=NULL;
		//	char *maj2;
			sendto(ear, "ip",sizeof("ip"),0, (struct sockaddr *) &sockaddr, sizeof(sockaddr));
			recvfrom(ear,rip, sizeof(rip), 0 ,NULL, NULL);
			sendto(ear, "hostname",sizeof("hostname"),0, (struct sockaddr *) &sockaddr, sizeof(sockaddr));
			recvfrom(ear,rhostname, sizeof(rhostname), 0 ,NULL, NULL);
			sprintf(maj,"INSERT INTO result (ip,hostname,pid,connected) VALUES (%s,%s,%d,1)",rip,rhostname,mypid);
			bdd_insert(maj);


			sprintf(buf,"[%d] Début d'échange de commande\n",pid);
			if(mkfifo(pipeperso, S_IRUSR | S_IWRITE | S_IWGRP)==-1 && errno != EEXIST){
				printf("Cannot make pipe\n"); 
			}
			while(!end){
				common=open((char *)pipeperso, O_RDONLY);
				read(common,todo,strlen(buf));
				//		read(common,todo[1],strlen(buf));
				//if(strcmp(todo[1],"quit")){
				//	end=1;
				//}
				//else{
				sendto(ear, buf,BUF_SIZ,0, (struct sockaddr *) &sockaddr, sizeof(sockaddr));
				printf("[%d] message envoye : %s\n",pid,buf);
				recvfrom(ear, buf,BUF_SIZ,0,NULL,NULL);
				sprintf(maj,"INSERT INTO result (idclient,idscript,result) VALUES (%d,%d,%s)",todo[1],todo[0],buf);
				bdd_insert(maj);
				//}
			}
			printf("[%d] close sockaddr\n",pid);
			close(ear);
			done=1;
		}
		else if ((childpid != 0)){//pere
		//	close(tun_serv[1]);
			printf("[%d] have fork, the child is [%d]\n",pid,childpid);
			demander_ordre(ordre,buf2);


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


int demander_ordre(int ordre[2],char *buf2){
	int choix =0; 
	int fait=0;
	int common;
	char *pipeperso=NULL;
	char *ord=NULL;
	while(!fait){
		system("clear");
		printf("Que voulez-vous faire ?\n");
		printf(" 1. Afficher les scripts disponibles\n");
		printf(" 2. Afficher les clients connectés\n");
		printf(" 3. Exectuter un script\n");
		printf(" Quel est votre choix (1, 2 ou 3) ? ");
		scanf("%d",&choix);
		if(choix==1){
			system("clear");
			afficher_script(buf2);
		}
		else if(choix==2){
			system("clear");
			afficher_client(buf2);
		}
		else if(choix==3){
			system("clear");
			ordre[0]=choix_script(buf2);
			system("clear");
			ordre[1]=choix_client(buf2);
		}
		fait=1;
	}
	common=open(pipeperso, O_WRONLY);
	sprintf(ord,"%d",ordre[0]);
	write(common,ord,strlen(ord));
	sprintf(ord,"%d",ordre[1]);
	write(common,ord,strlen(ord));
	close(common);
	exit(EXIT_SUCCESS);
}

