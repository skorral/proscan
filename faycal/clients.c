#include"stdio.h"  
#include"stdlib.h"  
#include"sys/types.h"  
#include"sys/socket.h"  
#include"string.h"  
#include"netinet/in.h"  
#include"netdb.h"

#define PORT 4444 //Je suis pas sur que fixer le port soit une bonne id�e, en effet si on fait des tests trop rapproch�s dans le temps, nous allons nous faire bloquer pr le syst�me.
#define BUF_SIZE 2000 //La taille du buffer est d�finie dans le fichier common/const.h

int main(int argc, char**argv) {  
	struct sockaddr_in addr, cl_addr;  
	int sockfd, ret;  
	char buffer[BUF_SIZE];  
	struct hostent * server;
	char * serverAddr;

	if (argc < 2) {
		printf("usage: client < ip address >\n");
		exit(1);  
	}

	serverAddr = argv[1]; 

	sockfd = socket(AF_INET, SOCK_STREAM, 0);  
	if (sockfd < 0) {  
		printf("Erreur dans la creation de la socket!!\n");  
		exit(1);  
	}  
	printf("La socket a �t� cr��e\n");   

	memset(&addr, 0, sizeof(addr));  
	addr.sin_family = AF_INET;  
	addr.sin_addr.s_addr = inet_addr(serverAddr);
	addr.sin_port = PORT;     

	ret = connect(sockfd, (struct sockaddr *) &addr, sizeof(addr));  
	if (ret < 0) {  
		printf("Erreur  dans la connexion au serveur!\n");  
		exit(1);  
	}

	printf("Connexion au serveur �tablie\n");  

	memset(buffer, 0, BUF_SIZE);
	printf(" message: ");

	while (fgets(buffer, BUF_SIZE, stdin) != NULL) {
		ret = sendto(sockfd, buffer, BUF_SIZE, 0, (struct sockaddr *) &addr, sizeof(addr));  
		if (ret < 0) {  
			printf("Erreur dans l'envoi des donn�es!\n\t-%s", buffer);  
		}
		ret = recvfrom(sockfd, buffer, BUF_SIZE, 0, NULL, NULL);  
		if (ret < 0) {  
			printf("Erreur dans la r�ception des donn�es!\n");    
		} else {
			printf("ont �t� re�us: ");
			fputs(buffer, stdout);
			printf("\n");
		}  
	}

	return 0;    
}  
