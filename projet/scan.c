#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <time.h>
#include <sys/stat.h>
#include <stdint.h>
#include <errno.h>
#include "scan.h"
#include "tree.h"
#include "md5sum.h"
#include "main.h"
#include "debug.h"

// lecture d'un répertoire (fonction récursive)
s_directory* process_dir(char* path){
	debug("processdir");
	char full_path[PATH_MAX];
	printf("%s\n",path);
	DIR* directory = opendir(path);
	if(directory==NULL){
		fprintf(stderr,"Erreur d'ouverture du répertoire %s\n",path);
		return NULL;
	}
	// création de la structure du répertoire
	s_directory* struct_dir;
	struct_dir=(s_directory*)malloc(sizeof(s_directory));
	char* directory_name = strrchr(path,'/');
	if(directory_name==NULL){
		directory_name=path;
	}else{
		directory_name=directory_name+1;
	}
	strcpy(struct_dir->name,directory_name);
	struct stat dir_stat;
	if (stat(path, &dir_stat) == 0){
		struct_dir->files=NULL;
		struct_dir->subdirs=NULL;
		struct_dir->next_dir=NULL;
		struct_dir->mod_time=dir_stat.st_mtime;
	}
	else{
		fprintf(stderr,"Erreur de stat sur répertoire %s\n",path);	
		return NULL;
	}
	// lecture du contenu du répertoire
	struct dirent* entry;
	while ((entry = readdir(directory))!=NULL) {
		printf("traitement de %s\n",entry->d_name);
		if(strcmp(entry->d_name,".")==0 || strcmp(entry->d_name,"..")==0)
			continue;

		sprintf(full_path,"%s/%s", path,entry->d_name);
		if(entry->d_type == DT_DIR){
			if(append_subdir(process_dir(full_path), struct_dir)!=0){
				fprintf(stderr,"Erreur lors de l'ajout du répertoire %s\n",full_path);	
				return NULL;
			}
		}
		else if(entry->d_type == DT_REG){
			if(append_file(process_file(full_path), struct_dir)!=0){
				fprintf(stderr,"Erreur lors de l'ajout du fichier %s\n",full_path);	
				return NULL;
			}
		}
		else{
			if(append_file(process_other(full_path), struct_dir)!=0){
				fprintf(stderr,"Erreur lors de l'ajout du fichier autre %s\n",full_path);	
				return NULL;
			}
		}
	}
	return struct_dir;
}

// scan d'un fichier classique
s_file* process_file(char* path){
	debug("processfile %s",path);
	s_file* struct_file;
	struct_file=(s_file*)malloc(sizeof(s_file));
	char* file_name = strrchr(path,'/');
	if(file_name==NULL){
		file_name=path;
	}else{
		file_name=file_name+1;
	}
	// création de la structure du fichier
	strcpy(struct_file->name,file_name);
	struct stat file_stat;
	if (stat(path, &file_stat) == 0){
		struct_file->next_file=NULL;
		struct_file->file_type=REGULAR_FILE;
		struct_file->mod_time=file_stat.st_mtime;
		struct_file->file_size=file_stat.st_size;
		if(get_compute_md5()==1){
			compute_md5(path,struct_file->md5sum);
		}else{
			struct_file->md5sum[0]='\0';
		}
	}
	else{
		fprintf(stderr,"Erreur de stat sur fichier %s\n",path);	
		return NULL;
	}
	debug("finprocessfile");
	return struct_file;
}

// scan d'un fichier autre
s_file* process_other(char* path){
	debug("processother");
	s_file* struct_other;
	struct_other=(s_file*)malloc(sizeof(s_file));
	char* other_name = strrchr(path,'/');
	if(other_name==NULL){
		other_name=path;
	}else{
		other_name=other_name+1;
	}
	// création de la structure du fichier
	strcpy(struct_other->name,other_name);
	struct stat other_stat;
	if (stat(path, &other_stat) == 0){
		struct_other->next_file=NULL;
		struct_other->file_type=OTHER_TYPE;
		struct_other->mod_time=other_stat.st_mtime;
		struct_other->md5sum[0]='\0';
	}
	else{
		fprintf(stderr,"Erreur de stat sur fichier autre %s\n",path);	
		return NULL;
	}
	return struct_other;
}

