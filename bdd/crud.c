#include <mysql/mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

MYSQL_RES *result = NULL;
int pas =0;

int bdd_select(char *qry,char *buf){
	MYSQL mysql;
	mysql_init(&mysql);
//	MYSQL_RES *result = NULL;
	MYSQL_ROW row;
	mysql_options(&mysql,MYSQL_READ_DEFAULT_GROUP,"option");
	unsigned int i = 0;
	unsigned int num_champs = 0;
	int j;
	pas++;
	printf("%d\n",pas);
	if(mysql_real_connect(&mysql,"127.0.0.1","root","athemisis","proscan",0,NULL,0)){
		j=mysql_query(&mysql,qry);
		//for(;;);
		printf("mysql result = %d\n",j);
		result = mysql_use_result(&mysql);
		printf("result = %p\n",result);
	//	result=malloc(sizeof(MYSQL_RES));
		num_champs = mysql_num_fields(result);
	//	exit(-1);
		while((row = mysql_fetch_row(result))){
			for(i=0;i< num_champs;i++){
				sprintf(buf+strlen(buf),"%s\n",row[i]);
			}
		}
		
		mysql_free_result(result);
		mysql_close(&mysql);
	}else{
		printf("Une erreur s'est produite lors de la connexion à la BDD!\n");
		mysql_close(&mysql);
	}
	return 0;
}

int bdd_delete(char *qry){
	MYSQL mysql;
	mysql_init(&mysql);
	mysql_options(&mysql,MYSQL_READ_DEFAULT_GROUP,"option");
	if(mysql_real_connect(&mysql,"127.0.0.1","proscan","","proscan",0,NULL,0)){
		mysql_query(&mysql,qry);
		mysql_close(&mysql);
	}else{      
		printf("Une erreur s'est produite lors de la connexion à la BDD!\n");
		mysql_close(&mysql);
	}
	return 0;
}

int bdd_update(char *qry){
	MYSQL mysql;
	mysql_init(&mysql);
	mysql_options(&mysql,MYSQL_READ_DEFAULT_GROUP,"option");
	if(mysql_real_connect(&mysql,"127.0.0.1","proscan","","proscan",0,NULL,0)){
		mysql_query(&mysql,qry);
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
	mysql_options(&mysql,MYSQL_READ_DEFAULT_GROUP,"option");
	if(mysql_real_connect(&mysql,"127.0.0.1","root","athemisis","proscan",0,NULL,0)){
		mysql_query(&mysql,qry);
		mysql_close(&mysql);
	}else{      
		printf("Une erreur s'est produite lors de la connexion à la BDD!\n");
		mysql_close(&mysql);
	}
	return 0;
}

