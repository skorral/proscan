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
#include "../common/net.h"

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
	sprintf(chaine,"./../script/user/script_%s.sh>resultat_script_client.txt",i);
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
	char buf[BUF_SIZ];
	FILE *fd_out;
	memset(buf, 0, BUF_SIZ);
	if(argc<3){
		printf("Usage : %s @server port_server\n",argv[0]);
		exit(EXIT_FAILURE);
	}
	printf("openConnection\n");
	if((sockfd = openConnection(argv[1], argv[2]))<0){
		perror("Connection failure");
	}
	fd_out = fopen("client_out","a+");
	if(!fd_out){
		printf("\aERREUR: Impossible d'ouvrir le fichier: %s.\n", fd_out);
	}
	printf("read\n");
	while(strcmp(buf,"quit")!=0){
		recvfrom(sockfd, buf, BUF_SIZ, 0 ,NULL, NULL);
		printf("message recu : %s\n",buf);
		fprintf(fd_out,"message recu : %s\n",buf);
		execution_script(buf);
	}
	printf("Close open fd\n");
	fclose(fd_out);	
	close(sockfd);
	printf("end of client\n");
	exit(EXIT_SUCCESS);
}
