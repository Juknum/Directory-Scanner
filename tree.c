#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

int append_subdir(s_directory *child, s_directory *parent) {

	// Si encore aucun enfant, le rajouter en tête de liste des sous-répertoires
	if (parent->subdirs==NULL)
		parent->subdirs = child;
	
	// Sinon ajouter l'enfant en fin de liste des enfants déjà présents
	else get_last_dir(parent->subdirs)->next_dir = child;
	return -1;
}

int append_file(s_file *child, s_directory *parent) {
	if (parent->files==NULL)
		parent->files = child;
	else
		get_last_file(parent->files)->next_file = child;
	
	return -1;
}

// Obtenir le dernier répertoire de même niveau de la liste chaînée
s_directory *get_last_dir(s_directory *dir) {
	if(dir!=NULL)
		while (dir->next_dir!=NULL)
			dir = dir->next_dir;
	return dir;
}

// Obtenir le dernier fichier de la liste chaînée
s_file *get_last_file(s_file *f) {
	if (f!=NULL)
		while (f->next_file!=NULL)
			f = f->next_file;
	return f;
}

// Suppression itérative de la liste de fichiers en désallouant la mémoire des éléments de la liste chaînée
void clear_files(s_directory *parent) {
	if(parent->files==NULL) return;
	
	// Libérer tous les éléments suivant le premier
	if(parent->files->next_file!=NULL)
		clear_next_files(parent->files);
	
	// Libérer le premier élément et supprimer son pointeur dans la structure du répertoire parent
	free(parent->files);
	parent->files = NULL;
}

void clear_next_files(s_file *prev) {
	if (prev==NULL || prev->next_file==NULL) return;
	
	// Exécuter d'abord récursivement cette fonction sur tous les éléments suivants
	if (prev->next_file->next_file!=NULL)
		clear_next_files(prev->next_file);
	
	// Libération de l'élément suivant effectuée après que tous les fichiers suivants aient été libérés 
	free(prev->next_file);
	prev->next_file = NULL;

}

// Suppression des sous-répertoires
void clear_subdirs(s_directory *parent) {
	// Ne rien faire si le parent n'existe pas ou si la liste des sous-répertoires est vide
	if (parent==NULL || parent->subdirs==NULL) return;
	
	// Libérer tous les sous-répertoires suivant le premier
	clear_next_dirs(parent->subdirs);
	
	// Libérer le tout premier sous-répertoire
	clear_subdirs(parent->subdirs);
	clear_files(parent->subdirs);
	free(parent->subdirs);
	parent->subdirs = NULL;
}

// Suppression de tous les répertoires de même niveau suivant celui passé en argument
void clear_next_dirs(s_directory *prev) {
	if (prev==NULL || prev->next_dir==NULL) return;
	
	// Exécuter d'abord récursivement cette fonction sur tous les éléments suivants
	if (prev->next_dir->next_dir!=NULL)
		clear_next_dirs(prev->next_dir);
	
	// Libération de l'élément suivant effectuée après que les dossiers suivants aient été libérés 
	clear_subdirs(prev->next_dir);
	clear_files(prev->next_dir);
	free(prev->next_dir);
	prev->next_dir = NULL;

}
