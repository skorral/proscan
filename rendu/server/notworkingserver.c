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
  exit(EXIT_SUCCESS);
}


int main(int argc, char **argv){
  int ear, listener;
  char buf[BUF_SIZ];
  struct sockaddr_in sockaddr;
//	ssize_t written=0;
  socklen_t addrlen = sizeof (sockaddr);
  memset(buf,'\0',BUF_SIZ);
  pid_t childpid;
  pid_t pid=getpid();
  int done=0;
  const char tun_serv[2];
  mkfifo(tun_serv,0666);
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
      int mypid=getpid();
      char *rip=NULL;
      char *rhostname=NULL;

      char * maj ="INSERT INTO client (ip,hostname, pid, connecte    d) VALUES (";
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
//			mkfifo(tun_"%d",0666,getpid());
//
      sprintf(buf,"[%d] Début d'échange de commande\n",pid);
      //printf("[%d] buffer = %s\n",pid,buf);
/*
      printf("[%d] Début du test de write\n",pid);
      if((written = sendto(ear, buf, BUF_SIZ,0, (struct sockaddr *) &sockaddr, sizeof(sockaddr)))==-1){
        perror("problem with Written");
        return errno;
      }
      printf("[%d] Fin du test du write\n",pid);
*/
      while(!end){
        //scanf("%s",buf);

        read(tun_serv[1],buf,sizeof(buf));
        if(strcmp(buf,"quit")){
          end=1;
        }
        else{
          //written =
          sendto(ear, buf,BUF_SIZ,0, (struct sockaddr *) &sockaddr, sizeof(sockaddr));
          printf("[%d] message envoye : %s\n",pid,buf);
          recvfrom(ear, buf,BUF_SIZ,0,NULL,NULL);
          write(tun_serv[0],buf,sizeof(buf));
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
