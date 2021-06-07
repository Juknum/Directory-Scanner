#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#include "debug.h"

// ajout d'un sous répertoir dans la structure
int append_subdir(s_directory* child, s_directory* parent){
	if(parent==NULL || child==NULL){
		return 0;
	}
	if(parent->subdirs==NULL){
		parent->subdirs=child;
		return 0;
	}
	s_directory* r_parent=parent->subdirs;
	while(r_parent->next_dir!=NULL){
		r_parent=r_parent->next_dir;
	}
	r_parent->next_dir=child;
	return 0;
}

// ajout d'un fichier dans la structure
int append_file(s_file* child, s_directory* parent){
	if(parent==NULL || child==NULL){
		return 1;
	}
	if(parent->files==NULL){
		parent->files=child;
		return 0;
	}
	s_file* r_parent=parent->files;
	while(r_parent->next_file!=NULL){
		r_parent=r_parent->next_file;
	}
	r_parent->next_file=child;
	return 0;
	
}

// libération des fichiers d'un répertoire
void clear_files(s_directory* parent){
	debug("clear_files");
	if(parent==NULL){
		return;
	}
	s_file* files=parent->files;
	s_file* next_file;
	while(files!=NULL){
		next_file=files->next_file;
		free(files);
		files=next_file;
	}
	debug("clear_files_exit");
}

// libération du répertoire
void clear_subdirs(s_directory* parent){
	debug("clear_dir");
	if(parent==NULL){
		return;
	}
	// on commence par libérer les fichiers
	clear_files(parent);
	s_directory* dirs=parent->subdirs;
	s_directory* next_subdir;
	// on fait la récursion sur tous les sous répertoires
	while(dirs!=NULL){
		next_subdir=dirs->next_dir;
		clear_subdirs(dirs);
		dirs=next_subdir;
	}
	// on libère le répertoire
	free(parent);
	debug("clear_dir_exit");
}
