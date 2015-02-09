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


void execution_script(char i) //Fonction permettant l'exécution de script local sur le client.
{
	char command[50];
        char *chaine;
        chaine = calloc(512,sizeof(char));
	strcpy(command, "./script_%c.sh",i);
system(command);
       // sprintf(chaine,"./../script/script_%c.sh>resultat_script_client.txt",i);
       // system(chaine);
}

int main(int argc, char *argv[]){
int d;
printf("saisir le num de script");
scanf("%d",&d);
execution_script(d);
}
