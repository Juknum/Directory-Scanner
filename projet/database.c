#include "database.h"
#include "sqlite3.h"
#include "debug.h"
#include "md5sum.h"
#include "openssl/md5.h"

sqlite3* db;
char sql[MAX_SQL_SIZE];
char md5_hexa[MD5_DIGEST_LENGTH*2+1];

// ouverture de la base de données
int open_db(){
	char* err_msg=NULL;
	int rc=sqlite3_open(DATABASE_NAME,&db);
	if(rc!=SQLITE_OK){
		fprintf(stderr,"Erreur d'ouverture de la base de donnees");
		return 1;
	}
	// suppression de la table si elle existe déja
	rc= sqlite3_exec(db,"DROP TABLE IF EXISTS filetable;",0,0,&err_msg);
	if(rc!=SQLITE_OK){
		fprintf(stderr,"Erreur d'ouverture %s\n",err_msg);
		sqlite3_free(err_msg);
		return 1;
	}
	// création de la table
	rc= sqlite3_exec(db,"CREATE TABLE filetable(file_type INTEGER, name TEXT, mod_time INTEGER, file_size INTEGER, md5sum TEXT);",0,0,&err_msg);
	if(rc!=SQLITE_OK){
		fprintf(stderr,"Erreur d'ouverture %s\n",err_msg);
		sqlite3_free(err_msg);
		return 1;
	}

	return 0;
}

// insertion du fichier dans la table
int insert_file(s_file* file){
	debug("insert_file %s", file->name);
	char* err_msg=NULL;
	convert_hexa(file->md5sum,md5_hexa);
	sprintf(sql,"INSERT INTO filetable(file_type,name,mod_time,file_size,md5sum) VALUES(%d,'%s',%ld,%ld,'%s');",file->file_type,file->name,file->mod_time,file->file_size,md5_hexa);
	int rc= sqlite3_exec(db,sql,0,0,&err_msg);
	if(rc!=SQLITE_OK){
		fprintf(stderr,"Erreur d'insertion (rc=%d) %s\n",rc,err_msg);
		sqlite3_free(err_msg);
		return 1;
	}
	debug("sortie_insert_file");
	return 0;
}

// insertion du répertoire dans la table
int insert_directory(s_directory* directory){
	debug("insert_directory");
	char* err_msg=NULL;
	sprintf(sql,"INSERT INTO filetable(file_type,name,mod_time) VALUES(%d,'%s',%ld);",DIRECTORY,directory->name,directory->mod_time);
	int rc= sqlite3_exec(db,sql,0,0,&err_msg);
	if(rc!=SQLITE_OK){
		fprintf(stderr,"Erreur d'insertion %s\n",err_msg);
		sqlite3_free(err_msg);
		return 1;
	}
	return 0;

}

// fermeture de la base de données
int close_db(){
	sqlite3_close(db);
	return 0;
}
