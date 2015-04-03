#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <signal.h>
#include <netdb.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include "../common/const.h"

int verif( char *test){     //Cette fonction permet de vérifier la non double inscription d'un serveur dans le fichier de log

	FILE * fichier;
	char s[128];

	if((fichier = fopen("../log/client/server_log.txt","a+"))==NULL){
		perror("[CLIENT] - ERROR in fopen");
		return -1;
	}
	while(fgets(s,128,fichier) != NULL){
		if(strcmp(s,test) == 0){
			fclose(fichier);
			return 1;
		}
	}

	fclose(fichier);
	return 2;
}

void inscription(char * ip_serveur, char * port){ //Cette fonction inscrit le serveur dans le fichier de log lors de la 1er connection
	/*if(argc != 3){
	  printf("Usage %s ip_server port\n",argv[0]);
	  exit(EXIT_SUCCESS);
	  }*/
	FILE * fichier;
	fichier = fopen("../log/client/server_log.txt","a+");
	fputs("*****************************\n",fichier);
	//fprintf(fichier,"le hostname du client est: %s\n",hostname_server); ne pas oublier de mettre le hostname en parametre : char * hostname_server
	fprintf(fichier,"L'adresse ip du serveur est: %s\n",ip_serveur);
	fprintf(fichier,"Le port du serveur est : %s\n",port);
	fputs("*****************************\n",fichier);
	fclose(fichier);

}

void execution_script(char *i) //Fonction permettant l'exécution de script local sur le client.
{
	
	char *chaine;
	chaine = calloc(512,sizeof(char));
	printf("fonc1\n");	
sprintf(chaine,"./../script/user/script_%s.sh>resultat_script_client_%s.txt",i,i);
	printf("fonc2\n");
	system(chaine);
}

void execution_script_recu(char *code){
	char *scan;
	scan = calloc(sizeof(code),sizeof(char));
	sprintf(scan,"%s\n",code);
	system(scan);
}


void supression_fichier_resultat()  // Fonction supprimant le fichier contenant les résultats du scan une fois qu'ils ont été passé au serveur
{
	char *chaine_2;
	chaine_2 = calloc(512,sizeof(char));
	sprintf(chaine_2,"rm resultat_script_*");
	system(chaine_2);
}


int main(int argc, char *argv[]) {
	int sockfd = -1;
	char buf[BUF_SIZ], result[128];
	FILE *fd_out;
	FILE * resultat;
	memset(buf, 0, BUF_SIZ);
	char s[4096];
	size_t tail;
	char *ip="127.0.0.1";
	char *hostname="ubuntu";
	char c;
	struct stat *info;
	if(argc<3){
		printf("Usage : %s @server port_server\n",argv[0]);
		exit(EXIT_FAILURE);
	}
	printf("openConnection\n");
	inscription(argv[1], argv[2]);



	struct sockaddr_in sock;

	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		printf("can't assign fd for socket");
		perror("socket");
		exit(EXIT_FAILURE);
	}
	memset(&sock, 0,sizeof(sock));
	sock.sin_family = AF_INET;
	inet_aton(argv[1], &(sock.sin_addr));
	sock.sin_port = htons(atoi(argv[2]));
	printf("connect\n");
	if (connect(sockfd, (struct sockaddr*) &sock, sizeof (sock)) == -1) {
		perror("Connection error");
		exit(EXIT_FAILURE);
	}
	printf("Connection Established\n");



	fd_out = fopen("client_out.txt","a+");
	if(!fd_out){
		printf("ERREUR: Impossible d'ouvrir le fichier: \"%s\"\n", fd_out);
	}
	printf("read\n");
	while(strcmp(buf,"quit")!=0){

		printf("Début échange de commande\n");

		recvfrom(sockfd, buf, BUF_SIZ, 0 ,NULL, NULL); //reception de la commande
		printf("1\n");
		//printf("message recu : %s\n",buf);
	////////	fprintf(resultat_script_client_1.txt"fd_out,"message recu : %s\n",buf);//enregistrement de la commande a executer dans le fichier de log
		printf("2\n");
	//	sleep(1);
		execution_script(buf); //execution de la commande
		printf("3\n");
		bzero(result,128);
		sprintf(result,"resultat_script_client_%s.txt",buf);
		resultat = fopen(result,"r"); //stockage local du resultat
	//	fstat(resultat,info);
	//	tail = info.st_size;
		printf("4\n");
	//	while (fread(s,tail,1,resultat) != NULL) {//envoi du resultat
		while(fgets(s, 4096, resultat) != NULL){
			printf("5\n");
			write(sockfd,s,128);
		}
		printf("6\n");
		supression_fichier_resultat(); //suppression du fichier local de resulatat
	}
	printf("Closecd open fd\n");
	fclose(fd_out);
	close(sockfd);
	//printf("end of client\n");
	exit(EXIT_SUCCESS);
}
