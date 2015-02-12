#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <mysql/mysql.h>

#define BUF_SIZE 2048

void login(int sock, fd_set lire,char name_user[]);
void mdp(int sock, fd_set lire, char login[]);
void adresse(int sock, fd_set lire);
void test_de_connexion(int sock, fd_set lire, char user[], char password[]);
int sockmax;
char IP[INET_ADDRSTRLEN];
void envoi_nas();

char name_user[30];
char utilisateur[1024];
char pwd[1024];
int pirate=0;

int main(int argc, char **argv)
{
	int sockfd, sockfd2;
	fd_set readfds;
	int t[FD_SETSIZE];
	int taille=0;
	char buf[1024];
	char *EMP;
	char validity[BUF_SIZE];
	char type_msg[BUF_SIZE];
	long size_msg;
	char datas[BUF_SIZE];
	//char *buf;
	int t_msg_r;
	pid_t status;


	struct sockaddr_in my_addr;
	struct sockaddr_in client;
	struct sockaddr_in nas;


	EMP=strdup("Thereisnolossofthisframe");


	socklen_t sin_size = sizeof(struct sockaddr_in);

	if(argc != 2)
	{
		printf("Usage: %s port_local\n", argv[0]);
		exit(-1);
	}

	sockfd = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);


	my_addr.sin_family = AF_INET;


	my_addr.sin_port = ntohs(atoi(argv[1]));


	my_addr.sin_addr.s_addr=htonl(INADDR_ANY);


	if(bind(sockfd,(struct sockaddr*)&my_addr,sizeof(my_addr)) != 0)
	{
		perror("Erreur lors de l'appel a bind -> ");
		exit(1);
	}



	if(listen(sockfd,10) != 0)
	{
		perror("Erreur lors de l'appel a listen -> ");
		exit(2);
	}

	printf("Attente de connexion\n");

	t[0]=sockfd;
	taille++;

	while(1)
	{
		FD_ZERO(&readfds);
		int j;
		sockmax=0;
		for(j=0; j<taille; j++)
		{
			if(t[j] != 0)
				FD_SET(t[j],&readfds);
			if(sockmax < t[j])
				sockmax = t[j];
		}

		if(select(sockmax+1,&readfds,NULL,NULL,NULL) == -1)
		{
			perror("Erreur lors de l'appel a select -> ");
			exit(1);
		}
		if(FD_ISSET(sockfd,&readfds))
		{
			if((sockfd2 = accept(sockfd,(struct sockaddr*)&client,&sin_size)) == -1)
			{
				perror("Erreur lors de accept -> ");
				exit(3);
			}
			inet_ntop(AF_INET, &(client.sin_addr), IP, INET_ADDRSTRLEN);
			printf("Connexion etablie avec %s\n", IP);
			taille++;
			t[taille-1]=sockfd2;
			do{
				pirate=0;
				login(sockfd2, readfds,utilisateur);
				mdp(sockfd2, readfds, utilisateur);
				//test_de_connexion(sockfd2,readfds ,utilisateur, pwd);
				send(sockfd2,"192.168.3.10",1024,0);
			}while(pirate!=0);
		}
	}

}

void login(int sock, fd_set lire,char name_user[])
{
	int i=1;

	if(send(sock,"Entre ton login :",1024,0) == -1)
	{
		perror("Erreur lors de l'appel a send -> ");
		exit(1);
	}
	puts("Je vais attendre");
	while(i)
	{
		FD_SET(sock,&lire);
		if(sockmax < sock)
			sockmax = sock;
		if(select(sockmax+1,&lire,NULL,NULL,NULL) == -1)
		{
			perror("Erreur lors de l'appel a select -> ");
			exit(1);
		}
		if(FD_ISSET(sock,&lire))
		{
			puts("YOLO");
			if(recv(sock,&utilisateur,1024,0) == -1)
			{
				perror("Erreur lors de la reception -> ");
				exit(4);
			}
			printf("Login : %s\n",utilisateur);
			strcpy(name_user,utilisateur); /* récuperation du nom de l'utilisteur */
			i=0;
		}
	}

}

void mdp(int sock, fd_set lire, char login[])
{
	int i=1;

	if(send(sock,"Entre ton mot de passe:",1024,0) == -1)
	{
		perror("Erreur lors de l'appel a send -> ");
		exit(1);
	}
	puts("Je vais attendre v2");
	while(i)
	{
		FD_SET(sock,&lire);
		if(sockmax < sock)
			sockmax = sock;
		if(select(sockmax+1,&lire,NULL,NULL,NULL) == -1)
		{
			perror("Erreur lors de l'appel a select -> ");
			exit(1);
		}
		if(FD_ISSET(sock,&lire))
		{
			puts("YOLO");
			if(recv(sock,&pwd,1024,0) == -1)
			{
				perror("Erreur lors de la reception -> ");
				exit(4);
			}
			printf("Mdp : %s\n",pwd);
			i=0;
		}
	}
	while(i<1024)
	{
		if(pwd[i] == '\n')
		{
			pwd[i] = '\0';
		}
		if(login[i] == '\n')
		{
			login[i] = '\0';
		}
		i++;
	}


}

void test_de_connexion(int sock, fd_set lire, char user[], char password[])
{
	MYSQL mysql;
	int j;
	mysql_init(&mysql);
	MYSQL_RES *resultat = NULL;
	MYSQL_ROW row = NULL;
	mysql_options(&mysql,MYSQL_READ_DEFAULT_GROUP,"option");
	if(mysql_real_connect(&mysql,"127.0.0.1","test","test","NAS",0,NULL,0))
	{
		char requete[200];
		sprintf(requete, "SELECT * FROM `ID` WHERE utilisateur = '%s' AND mdp = '%s'", user, password);
		if(mysql_query(&mysql, requete))
		{
			puts("flute");
			return;
		}
		int i = 0;
		resultat = mysql_store_result(&mysql);
		while(row = mysql_fetch_row(resultat))
		{
			i++;
		}
		if(i != 0)
		{
			char msg[1024];
			sprintf(msg, "Bienvenue %s\n", user);
			if(send(sock,msg,1024,0) == -1)
			{
				perror("Erreur lors de l'appel a send -> ");
				exit(1);
			}

		}
		else

		{
			char msg[1024];
			sprintf(msg, "Nom d'utilisateur ou mot de passe incorrect\n", user);
			pirate=1;
			if(send(sock,msg,1024,0) == -1)
			{
				perror("Erreur lors de l'appel a send -> ");
				exit(1);
			}
		}
		mysql_close(&mysql);
	}
	else
	{
		if(send(sock,"Erreur lors de la connexion à la BDD",1024,0) == -1)
		{
			perror("Erreur lors de l'appel a send -> ");
			exit(1);
		}
	}
	adresse(sock, lire);
}

void adresse(int sock, fd_set lire)
{
	int i = 1;
	MYSQL mysql;
	int j;
	mysql_init(&mysql);
	MYSQL_RES *resultat = NULL;
	MYSQL_ROW row = NULL;
	char nom[1024];
	char ip[20];
	if(send(sock,"Entre le nom du serveur :\n",1024,0) == -1)
	{
		perror("Erreur lors de l'appel a send -> ");
		exit(1);
	}
	while(i)
	{
		FD_SET(sock,&lire);
		if(sockmax < sock)
			sockmax = sock;
		if(select(sockmax+1,&lire,NULL,NULL,NULL) == -1)
		{
			perror("Erreur lors de l'appel a select -> ");
			exit(1);
		}
		if(FD_ISSET(sock,&lire))
		{
			if(recv(sock,&nom,1024,0) == -1)
			{
				perror("Erreur lors de la reception -> ");
				exit(4);
			}
			printf("Serveur : %s\n",nom);
			i=0;
		}
	}
	i=0;
	while(i<1024)
	{
		if(nom[i] == '\n')
		{
			nom[i] = '\0';
		}
		i++;
	}

	mysql_options(&mysql,MYSQL_READ_DEFAULT_GROUP,"option");
	if(mysql_real_connect(&mysql,"127.0.0.1","test","test","NAS",0,NULL,0))
	{
		char requete[200];
		sprintf(requete, "SELECT ip FROM `DNS` WHERE nom = '%s'", nom);
		if(mysql_query(&mysql, requete))
		{
			puts("flute");
			return;
		}
		i = 0;
		resultat = mysql_store_result(&mysql);
		unsigned int num_champs = mysql_num_fields(resultat);
		unsigned int w;
		while ((row = mysql_fetch_row(resultat)))
		{
			unsigned long *lengths;
			lengths = mysql_fetch_lengths(resultat);
			for(w = 0; w < num_champs; w++)
			{
				printf("%.*s ", (char) lengths[w], row[w] ? row[w] : "NULL");
				sprintf(ip, "%.*s ", (char) lengths[w], row[w] ? row[w] : "NULL");
			}
			i++;
		}
		if(i != 0)
		{
			envoi_nas();
		}
		else

		{
			char msg2[1024];
			sprintf(msg2, "Serveur inconnu\n");
			if(send(sock,msg2,1024,0) == -1)
			{
				perror("Erreur lors de l'appel a send -> ");
				exit(1);
			}
		}
		mysql_close(&mysql);
	}
	else
	{
		if(send(sock,"Erreur lors de la connexion à la BDD",1024,0) == -1)
		{
			perror("Erreur lors de l'appel a send -> ");
			exit(1);
		}
	}
}

void envoi_nas()
{
	int sock2;
	char truc[]="192.168.3.10";
	char truc2[]="192.168.3.11";
	struct sockaddr_in serveur;
	sock2 = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	serveur.sin_family = AF_INET;
	inet_aton(truc, &(serveur.sin_addr));
	serveur.sin_port = htons(1235);
	if(connect(sock2,(struct sockaddr*)&serveur,sizeof(serveur)) == -1)
	{
		perror("Erreur de connexion -> ");
		exit(2);
	}
	if(send(sock2,IP,1024,0) == -1)
	{
		perror("Erreur lors de l'appel a send -> ");
		exit(1);
	}
	if(send(sock2,name_user,30,0) == -1){ /*envoi du nom de l'utilisateur au NAS*/
		perror("Erreur lors de l'appel a send -> ");
		exit(1);
	}
	close(sock2);
}

char *concat(char *buf,char *validity,int size_msg, char *type_msg, char *datas){
	char delim='/';
	char *tmp;
	buf=strcat(buf,validity);
	buf=strcat(buf,&delim);
	sprintf(tmp, "%d",size_msg);
	buf=strcat(buf,tmp);
	buf=strcat(buf,&delim);
	buf=strcat(buf,type_msg);
	buf=strcat(buf,&delim);
	buf=strcat(buf,datas);
	return buf;
}

void deconcat(char *buf,char *validity,int size_msg, char *type_msg, char *datas){
	char delim='/';
	validity=strtok(buf,"/");
	sscanf(buf,"%d",&size_msg);
	//	&size_msg=strtok(buf,"/");
	type_msg=strtok(buf,"/");
	datas=strtok(buf,"/");
}

