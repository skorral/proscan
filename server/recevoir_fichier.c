#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
void recevoir_fichier(int id, char *buf);
int parseARGS(char **args, char *line);

int parseARGS(char **args, char *line){
	int tmp=0;
	args[tmp] = strtok( line, ":" );
	while ( (args[++tmp] = strtok(NULL, ":" ) ) != NULL );
	return tmp - 1;
}

void recevoir_fichier(int id, char *buf){
	int count1=1,count2=1, pourcentage;
	char *header[4096];
	char recvBUFF[4096];
	char *nom_fic, *fichierSIZE;
	FILE * recvFILE;
	int yaha=1;
	int recep = 0;
	char tempstr[4096];
	puts("YOUPS!!");
	while(1)
	{
		if( recv(id, recvBUFF, sizeof(recvBUFF), 0) )
		{
			if(!strncmp(recvBUFF,"FBEGIN",6))
			{
				recvBUFF[strlen(recvBUFF) - 2] = 0;
				parseARGS(header, recvBUFF);
				nom_fic = header[1];
				fichierSIZE = header[2];
			}
			recvBUFF[0] = 0;
			recvFILE = fopen ( nom_fic,"w" );

			pourcentage = atoi( fichierSIZE ) / 100;
			while(1)
			{
				if( recv(id, recvBUFF, 1, 0) != 0 )
				{
					fwrite (recvBUFF , sizeof(recvBUFF[0]) , 1 , recvFILE );

					if( count1 == count2 )
					{
						printf("33[0;0H");
						printf( "\33[2J");
						puts("oui");
						printf("Nom fichier: %s\n", nom_fic);
						printf("Taille fichier: %d Kb\n", atoi(fichierSIZE) / 1024);
						printf("Pourcentage : %d%% ( %d Kb)\n",count1 / pourcentage ,count1 / 1024);
						count1+=pourcentage;
					}
					count2++;
					recep++;
					recvBUFF[0] = 0;
					if((count1 /pourcentage)>=100)
					{
						system("clear");
						return;
					}
				}
				else
				{
					return;
				}
			}
		}
		return;
	}
}

