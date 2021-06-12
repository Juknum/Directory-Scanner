#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>

#include "../headers/definitions.h"
#include "../headers/scan.h"
#include "../headers/tree.h"

char* recuperation_nom(char * path) {
	long int l = strlen(path);
	char *nom = malloc(l + 1);
	long int index = -1;

	// On remonte la chaîne de charactères pour trouver le premier / et prendre son index
	for (long int i = l - 1; i >= 0; i--) {
		if (path[i] == '/') {
			index = i + 1;
			break;
		}
		
	}

	// si non trouvé:
	if (index == -1) strcpy(nom, path);
	// sinon on ajoute les charactères depuis l'index jusqu'à "l"
	else {
		for (long int n = 0; n < l && index + n < l; n++) {
			nom[n] = path[n + index];
		}
		nom[l - index] = '\0';
	}

	return nom;
}

s_file *process_file(char *path){

	//structures de manipulation de fichier
	struct stat stats;

	//lecture de l'etat du fichier
	stat(path, &stats);

	//fichier courant a scanner
	s_file *parent;
	parent = malloc(sizeof(s_file));

	//Champs du fichier
	//-----------------
	if(S_ISREG(stats.st_mode)){
		parent->file_type = REGULAR_FILE;
		parent->file_size = stats.st_size;
		//md5sum
		snprintf(parent->md5sum, sizeof(parent->md5sum), "WIP");
	}
	else {
		parent->file_type = OTHER_TYPE;
	}
	snprintf(parent->name, sizeof(parent->name), "%s", recuperation_nom(path));
	parent->mod_time = stats.st_mtime;

	return parent;
}

s_directory *process_dir(char *root_path) {

	DIR *descripteur;
	struct dirent *dirent = NULL;
	struct stat stats;

	s_directory *root;
	root = malloc(sizeof(s_directory));

	stat(root_path, &stats);

	// init dir
	snprintf(root->name, sizeof(root->name), "%s", recuperation_nom(root_path));
	root->mod_time = stats.st_mtime;
	root->subdirs  = NULL;
	root->files    = NULL;
	root->next_dir = NULL;

	// ouverture du répertoire
	descripteur = opendir(root_path);
	if (descripteur == NULL) return NULL; // impossible d'ouvrir le répertoire

	// tant qu'il y a des éléments dans le répertoire
	char *path = (char *)malloc(2048 * sizeof(char));

	while((dirent = readdir(descripteur)) != NULL) {
		// on évite de traiter les . et .. (boule infinie)
		if (strcmp(dirent->d_name, ".") == 0 || strcmp(dirent->d_name, "..") == 0) {
			continue;
		}

		snprintf(path, 2048, "%s", root_path);
		strcat(path, "/"); strcat(path, dirent->d_name);

		// lecture impossible -> on passe au suivant & on affiche l'erreur
		if (stat(path, &stats) == -1) {
			perror("stat");
			continue;
		}

		// si c'est un dossier
		if (S_ISDIR(stats.st_mode) != 0) {
			// si c'est le premier sous-dossier
			if (root->subdirs == NULL) root->subdirs = process_dir(path);
			// sinon on l'attache au sous-dossier précédent
			else {
				s_directory *next_subdir;
				next_subdir = root->subdirs;
				while (next_subdir->next_dir != NULL) next_subdir = next_subdir->next_dir;
				next_subdir->next_dir = process_dir(path);
			}
		}

		// si c'est un fichier
		if (S_ISREG(stats.st_mode) != 0) {

			// si c'est le premier fichier
			if (root->files == NULL) root->files = process_file(path);
			// sinon on l'attache au fichier précédent
			else {
				s_file *file;
				file = root->files;
				while (file->next_file != NULL) file = file->next_file;
				file->next_file = process_file(path);
			}

		}
		

	}

	closedir(descripteur);
	return root;
}