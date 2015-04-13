void envoi_fichier(int id_client, char *nom_fichier, char *destination)
{
	char temp[1024];
	FILE * fichier_envoi;
	int c;
	char save[1];
	char remoteFILE[4096];
	long fichierSIZE;
	int compt1=1,compt2=1, pourcentage;

	sprintf(temp, "%s/", chemin);

	strcat(temp, nom_fichier);
	printf("Chemin + fichier = %s\n", temp);
	if(destination=="" || destination==" ")
	{   
		destination="fichier_recu";
	}   
	fichier_envoi = fopen (temp,"r");
	if(!fichier_envoi)
	{   
		printf("Erreur ouverture fichier\n");
	}   

	else
	{   

		fseek (fichier_envoi, 0, SEEK_END);
		fichierSIZE = ftell (fichier_envoi);
		rewind(fichier_envoi);//retour debut fichier

		sprintf(remoteFILE,"FBEGIN:%s:%li\r\n", destination, fichierSIZE);
		send(id_client, remoteFILE, sizeof(remoteFILE), 0); 

		pourcentage = fichierSIZE / 100;
		while((c=getc(fichier_envoi))!=EOF)
		{   
			save[0] = c;
			send(id_client, save, 1, 0); 
			if( compt1 == compt2 ) { 
				printf("33[0;0H");
				printf( "\33[2J");
				printf("Nom fichier: %s\n", temp);
				printf("Taille fichier: %li Kb\n", fichierSIZE / 1024);
				printf("Pourcentage : %i%% ( %i Kb)\n",compt1 / pourcentage ,compt1 / 1024);
				compt1+=pourcentage;
			}
			compt2++;

		}
	}
}
