#include <stdio.h>
#include <time.h>
#include <string.h>
#include "save.h"
#include "database.h"
#include "debug.h"
#include "md5sum.h"

// fichier dans lequel faire la sauvegarde
FILE* target_file;
// somme md5 en hexadécimal
char md5_hexa[MD5_DIGEST_LENGTH*2+1];
// date de dernière modification d'un fichier
struct tm* date;
// chemin complet d'un fichier
char full_path[PATH_MAX];

// sauvegarde dans le fichier
int save_to_file(s_directory *root, char *path_to_target){
	strcpy(full_path,root->name);
	target_file=fopen(path_to_target,"w");
	fprintf(target_file,"0\t");
	date=localtime(&root->mod_time);
	fprintf(target_file,"%02d/%02d/%04d %02d:%02d\t",date->tm_mday,date->tm_mon+1,date->tm_year+1900,date->tm_hour,date->tm_min);
	fprintf(target_file,"%s/\n",full_path);
	write_subdirs(root,strlen(root->name));
	fclose(target_file);
}

// sauvegarde dans la base de données
int save_to_db(s_directory *root){
	open_db();
	insert_subdirs(root);
	close_db();
}

// insertion des fichiers dans la base de données
void insert_files(s_directory* parent){
	debug("insert_files");
	if(parent==NULL){
		return;
	}
	s_file* files=parent->files;
	s_file* next_file;
	while(files!=NULL){
		next_file=files->next_file;
		insert_file(files);
		files=next_file;
		debug("fichier suivant");
	}
	debug("insert_files_exit");
}

// insertion des sous répertoires dans la base de données
void insert_subdirs(s_directory* parent){
	debug("insert_subdirs");
	if(parent==NULL){
		return;
	}
	insert_files(parent);
	s_directory* dirs=parent->subdirs;
	s_directory* next_subdir;
	// insertion des sous répertoires
	while(dirs!=NULL){
		next_subdir=dirs->next_dir;
		insert_directory(dirs);
		dirs=next_subdir;
	}
	dirs=parent->subdirs;
	// récursion
	while(dirs!=NULL){
		next_subdir=dirs->next_dir;
		insert_subdirs(dirs);
		dirs=next_subdir;
	}
	debug("insert_subdirs_exit");
}

// écriture des fichier dans le fichier de sauvegarde
void write_files(s_directory* parent,int pos){
	debug("write_files");
	if(parent==NULL){
		return;
	}
	s_file* files=parent->files;
	s_file* next_file;
	while(files!=NULL){
		sprintf(full_path+pos,"/%s",files->name);
		next_file=files->next_file;
		fprintf(target_file,"%d\t",files->file_type);
		date=localtime(&files->mod_time);
		fprintf(target_file,"%02d/%02d/%04d %02d:%02d\t",date->tm_mday,date->tm_mon+1,date->tm_year+1900,date->tm_hour,date->tm_min);
		if(files->file_type!=2)
			fprintf(target_file,"%ld\t",files->file_size);
		if(files->md5sum[0]!='\0'){
			// on ne met pas de \t si le champs est vide
			convert_hexa(files->md5sum,md5_hexa);
			fprintf(target_file,"%s\t",md5_hexa);
		}
		fprintf(target_file,"%s\n",full_path);
		files=next_file;
		debug("fichier suivant");
	}
	debug("write_files_exit");

}

// écriture des sous répertoires dans le fichier de sauvegarde
void write_subdirs(s_directory* parent,int pos){
	debug("write_subdirs");
	if(parent==NULL){
		return;
	}
	write_files(parent,pos);
	s_directory* dirs=parent->subdirs;
	s_directory* next_subdir;
	// écriture des fichiers
	while(dirs!=NULL){
		sprintf(full_path+pos,"/%s",dirs->name);
		next_subdir=dirs->next_dir;
		fprintf(target_file,"0\t");
		date=localtime(&dirs->mod_time);
		fprintf(target_file,"%02d/%02d/%04d %02d:%02d\t",date->tm_mday,date->tm_mon+1,date->tm_year+1900,date->tm_hour,date->tm_min);
		fprintf(target_file,"%s/\n",full_path);
		dirs=next_subdir;
	}
	dirs=parent->subdirs;
	// récursion
	while(dirs!=NULL){
		next_subdir=dirs->next_dir;
		sprintf(full_path+pos,"/%s",dirs->name);
		write_subdirs(dirs,pos+strlen(dirs->name)+1);
		dirs=next_subdir;
	}
	debug("insert_subdirs_exit");
}
