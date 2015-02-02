#include <mysql/mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *bdd_select(char *qry){
	MYSQL mysql;
	mysql_init(&mysql);
	mysql_res *result = NULL;
	mysql_row row;
	/*mysql_options(&mysql,MYSQL_READ_DEFAULT_GROUP,"option");*/
	int i = 1;
	char *buf = [];
	if(mysql_real_connect(&mysql,"127.0.0.1","proscan","","proscan",0,NULL,0)){
		mysql_query(&mysql,qry);
		result = mysql_use_result(&mysql);
		while((row = mysql_fetch_row(result))){
			sprintf(buf,"Result : %ld\n",i);
			i++;
		}
		mysql_free_result(result);
		mysql_close(&mysql);
	}else{
		printf("Une erreur s'est produite lors de la connexion à la BDD!\n");
		mysql_close(&mysql);
	}
	return buf;
}

int bdd_delete(void){
	MYSQL mysql;
	mysql_init(&mysql);
	int n;
	/*mysql_options(&mysql,MYSQL_READ_DEFAULT_GROUP,"option");*/
	if(mysql_real_connect(&mysql,"127.0.0.1","proscan","","proscan",0,NULL,0)){
		n=mysql_affected_rows(MYSQL *mysql);
		mysql_close(&mysql);
	}else{      
		printf("Une erreur s'est produite lors de la connexion à la BDD!\n");
		mysql_close(&mysql);
	}
	return 0;
}

int bdd_update(void){
	MYSQL mysql;
	mysql_init(&mysql);
	int n;
	/*mysql_options(&mysql,MYSQL_READ_DEFAULT_GROUP,"option");*/
	if(mysql_real_connect(&mysql,"127.0.0.1","proscan","","proscan",0,NULL,0)){
		n=mysql_affected_rows(MYSQL *mysql);
		mysql_close(&mysql);
	}else{      
		printf("Une erreur s'est produite lors de la connexion à la BDD!\n");
		mysql_close(&mysql);
	}
	return 0;
}

int bdd_insert(char *qry){
	MYSQL mysql;
	mysql_init(&mysql);
	/*mysql_options(&mysql,MYSQL_READ_DEFAULT_GROUP,"option");*/
	/*char *ip;
	char *fd;*/
	int n;
	
	/*strcpy(ip,addr);
	strcpy(fd,file_descriptor);*/
	if(mysql_real_connect(&mysql,"127.0.0.1","proscan","","proscan",0,NULL,0)){
		mysql_query(&mysql,qry);
		//mysql_query(&mysql,"INSERT INTO client ip:port,fd VAlUES(ip,fd)");
		n=mysql_affected_rows(&mysql);
		printf("Nombre de colonne affecté = %d\n",n);

		mysql_close(&mysql);
	}else{      
		printf("Une erreur s'est produite lors de la connexion à la BDD!\n");
		mysql_close(&mysql);
	}
	return 0;
}

int bdd_create(void){
	MYSQL mysql;
	mysql_init(&mysql);
	/*mysql_options(&mysql,MYSQL_READ_DEFAULT_GROUP,"option");*/
	if(mysql_real_connect(&mysql,"127.0.0.1","proscan","","proscan",0,NULL,0)){
		mysql_close(&mysql);
	}else{
		printf("Une erreur s'est produite lors de la connexion à la BDD!\n");
		mysql_close(&mysql);
	}
	return 0;
}
/*
int main(void){
	MYSQL mysql;
	MYSQL_RES resultat = NULL;
	MYSQL_ROW row;
	int n,i=1;
	unsigned long *lengths;
	unsigned int c = 0;
	unsigned int num_champs = 0;
	mysql_init(&mysql);
	mysql_options(&mysql,MYSQL_READ_DEFAULT_GROUP,"option");

	if(mysql_real_connect(&mysql,"127.0.0.1","proscan","","client",0,NULL,0)){

		mysql_query(&mysql, "INSERT INTO client ip:port,fd VALUES('127.0.0.1', '12586'),('192.168.0.1','12548')");

		n=mysql_affected_rows(&mysql);
		printf("Nombre de colonne affecté = %d\n",n);

		mysql_query(&mysql, "SELECT * FROM client");
		resultat = mysql_use_result(&mysql);
		num_champs = mysql_num_fields(resultat);
		while ((row=mysql_fetch_row(resultat))){
			lengths = mysql_fetch_lengths(result);
			for(i = 0; i < num_champs; i++){
				printf("[%.*s] ", (int) lengths[i], row[i] ? row[i] : "NULL");
			}
			printf("\n");
		}

		mysql_free_result(resultat);

		mysql_close(&mysql);

	}else{
		printf("Une erreur s'est produite lors de la connexion à la BDD!");
	}


	return 0;
}
*/
