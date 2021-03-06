#include "../headers/save.h"

int save_to_file(s_directory *root, char *path_to_target, int nb_tabs, char *path_to_current_dir, bool doMD5) {
	FILE *f = fopen(path_to_target, "a");
	if (!f) return -1;

	// Ajout du nombre de tabulation nécessaire (indentation)
	char tabs[nb_tabs + 2];
	for (size_t i = 0; i < nb_tabs; i++) tabs[i] = '\t';
	tabs[nb_tabs] = '\0';

	// Ajout des info du dossier actuel
	fputs(tabs, f);
	fputs(string_builder_of_dir(*root, path_to_current_dir), f);
	fputs("\n", f);
	tabs[nb_tabs] = '\t';
	tabs[nb_tabs + 1] = '\0';

	// Ecriture des fichiers
	s_file *current_file = root->files;
	while (current_file != NULL) {
		fputs(tabs, f);
		fputs(string_builder_of_file(*current_file, path_to_current_dir, doMD5), f);
		fputs("\n", f);
		current_file = current_file->next_file; // Fichier suivant
	}
	free(current_file);
	fclose(f); // On ferme le fichier maintenant car on le réouvre dans la récurrence

	// Ecriture des sous-dossiers
	s_directory *current_dir;
	current_dir = root -> subdirs;
	char *next_dir_path = (char *)malloc(4096 * sizeof(char));

	while (current_dir != NULL) {
		// Récurrence
		strcpy(next_dir_path, path_to_current_dir);
		strcat(next_dir_path, "/"); strcat(next_dir_path, current_dir->name);
		save_to_file(current_dir, path_to_target, nb_tabs + 1, next_dir_path, doMD5);
		current_dir = current_dir->next_dir;
	}
	
	free(current_dir);
	free(next_dir_path);

	return 0;
}

char* string_builder_of_dir(s_directory dir, char *path_to_parent_dir) {
	char time[32];
	char *buffer = (char *)malloc(4096 * sizeof(char));

	// code e_type
	strcpy(buffer, "0"); // dir e_type
	strcat(buffer, "\t");

	// date
	strftime(time, 32, "%Y-%m-%d-%H:%M:%S", localtime(&dir.mod_time));
	strcat(buffer, time); strcat(buffer, "\t");

	// chemin
	strcat(buffer, path_to_parent_dir);
	strcat(buffer, "/");

	return buffer;
}

char* string_builder_of_file(s_file file, char *path_to_parent_dir, bool doMD5) {
	char time[32];
	char *buffer = (char *)malloc(4096 * sizeof(char));

	// code e_type
	if (file.file_type == REGULAR_FILE){
		strcpy(buffer, "1"); // file e_type
	}
	else strcpy(buffer, "2");
	strcat(buffer, "\t");

	// date
	strftime(time, 32, "%Y-%m-%d-%H:%M:%S", localtime(&file.mod_time));
	strcat(buffer, time); strcat(buffer, "\t");


	if (file.file_type == REGULAR_FILE) {
		// taille
		char * size;
		size = malloc(sizeof(file.file_size));
		snprintf(size, sizeof(buffer), "%lu" ,file.file_size);
		strcat(buffer,size); strcat(buffer, "\t");
		// md5sum
		if (doMD5 == true) {
			strcat(buffer, file.md5sum); strcat(buffer, "\t");
		}
	}

	// chemin
	strcat(buffer, path_to_parent_dir); strcat(buffer, "/"); strcat(buffer, file.name);

	return buffer;
}
