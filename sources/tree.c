#include "../headers/tree.h"

void clear_files(s_file *parent) {
	if(parent->next_file != NULL) clear_files(parent->next_file);
	free(parent);
}

void clear_subdirs(s_directory *parent) {
	if(parent->files != NULL) clear_files(parent->files);
	if(parent->subdirs != NULL) clear_subdirs(parent->subdirs);
	if(parent->next_dir != NULL) clear_subdirs(parent->next_dir);
	free(parent);
}

bool append_subdir(s_directory *child, s_directory *parent) {
	if (parent == NULL) return false;

	// Si le répertoire parent à déjà un sous-dossier, on l'attache à celui ci
	if (parent->subdirs) {
		s_directory *temp = parent->subdirs;
		while (temp->next_dir) temp = temp->next_dir;
		temp->next_dir = child;
	} else parent->subdirs = child;

	return true;
}


bool append_file(s_file *child, s_directory *parent) {
	if (parent == NULL) return false;

	if (parent->files) {
		s_file *temp = parent->files;
		while (temp->next_file) temp = temp->next_file;
		temp->next_file = child;
	} else parent->files = child;

	return true;
}