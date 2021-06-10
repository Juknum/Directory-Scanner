#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <errno.h>
#include "scan.h"
#include "tree.h"

s_file *process_file(char *path, char * nom){

	printf("_Entree dans process_file_\n");

	//structures de manipulation de fichier
	struct stat stats;

	//lecture de l'etat du fichier
	stat(path, &stats);

	//fichier courant a scanner
	s_file * parent;
	parent = malloc(sizeof(s_file));

	//Champs du fichier
	//-----------------
	if(S_ISREG(stats.st_mode)){
		parent->file_type = 1;
		parent->file_size = stats.st_size;
		//md5sum
	}
	else{
		parent->file_type = 3;
	}
	snprintf(parent->name, sizeof(parent->name), "%s", nom);
	parent->mod_time = stats.st_mtime;
	printf("_Sortie de process_file_\n");

	return parent; 
}

s_directory *process_dir(char *path, char *nom){

	printf("_Entree dans process_dir_\n");

	//structures de manipulation de fichier
	DIR *descripteur;
	struct dirent *dirent = NULL;
	struct stat stats;

	//dossier courant a scanner
	s_directory * parent;
	parent = malloc(sizeof(s_directory));

	//Chemin de l'element
	char chemin[200];

	///lecture de l'etat du dossier
	stat(chemin, &stats);

	//Champs par default du dossier
	//-----------------------------
	snprintf(parent->name, sizeof(parent->name), "%s", nom);
	parent->mod_time = stats.st_mtime;
	parent->subdirs = NULL;
	parent->files = NULL;
	parent->next_dir = NULL;

	//lecture du contenu du dossier
	descripteur=opendir(path);
	dirent=readdir(descripteur);

	//scan dossier intermediaire pour le scan
	s_directory * dir1;
	s_directory * dir0 = NULL;

	//scan fichier intermediaire pour le scan
	s_file * file1;
	s_file * file0 = NULL;

	//Boucle de lecture du dossier//
	//============================//
	while(dirent!=NULL) {

		printf("Element lu %s\n",dirent->d_name);
		
		//Verifie si l'element du dossier n'est pas .. ou .
		if(strcmp(dirent->d_name,"..")==0 || strcmp(dirent->d_name,".")==0 ){
			printf("Mauvais element (.. ou .)\n\n");
			dirent=readdir(descripteur);
			continue;
		}

		//Creation du string chemin complet
		snprintf(chemin, 200, "%s", path);	
		strcat(chemin,"/");
		strcat(chemin,dirent->d_name);
		
		printf("Le chemin est : %s\n",chemin);



		//Si la lecture de l'etat de l'element est possible
		//-------------------------------------------------
		if( (stat(chemin, &stats)) == 0 && (strcmp(dirent->d_name,"..")!=0 || strcmp(dirent->d_name,".")!=0 ) ){
			printf("Element lu est possible\n");

			//Element est un dossier//
			//----------------------//
			if(S_ISDIR(stats.st_mode)){
				printf("C'est un dossier \n\n");
				//scan le sous dossier
				dir1 = process_dir(chemin,dirent->d_name);
				
				//Un sous dosier a deja ete creer
				if(dir0 != NULL){
					printf("Nouveau sous dossier de %s : %s",parent->name,dir1->name);
					dir0->next_dir = dir1;
					dir0 = dir1;
				}
				//Premier sous dossier
				else{
					printf("Premier sous dossier de %s est %s\n",parent->name,dir1->name);
					parent->subdirs = dir1;
					dir0 = dir1;
				}
				printf("\n");
			}
			//Element est un fichier//
			//----------------------//
			else if(S_ISREG(stats.st_mode)){
				printf("C'est un fichier regulier\n\n");

				//scan le fichier
				file1 = process_file(chemin,dirent->d_name);
				
				//Un fichier a deja ete creer
				if(file0 != NULL){
					printf("Nouveau fichier de %s : %s",parent->name,file1->name);
					file0->next_file = file1;
					file0 = file1;
				}
				//Premier fichier
				else{
					printf("Premier fichier de %s est %s\n",parent->name,file1->name);
					parent->files = file1;
					file0 = file1;
				}
				printf("\n");
			}
			//ERREUR
			else{ printf("Erreur, type de l'element impossible\n"); return NULL;}
		}
		//ERREUR
		else{ printf("Erreur, lecture etat de l'element impossible\n"); return NULL; }

		//Lis l'element suivant du dossier
		dirent=readdir(descripteur);
	}
	closedir(descripteur);

	printf("_Sortie de process_dir_\n");

	return parent;
}


/*
void main() {

	

	s_directory * parent = process_dir("source","source");
	printf("Fin scan\n");
	clear_subdirs(parent);


}*/
