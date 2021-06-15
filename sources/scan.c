#include "../headers/md5sum.h"
#include "../headers/scan.h"
#include "../headers/tree.h"

char* recuperation_nom(char * path) {
	long int l = strlen(path);
	char *nom = malloc(l + 1);
	long int index = -1;

	// On remonte la chaîne de caractères pour trouver le premier / et prendre son index
	for (long int i = l - 1; i >= 0; i--) {
		if (path[i] == '/') {
			index = i + 1;
			break;
		}
		
	}

	// si non trouvé:
	if (index == -1) strcpy(nom, path);
	// sinon on ajoute les caractères depuis l'index jusqu'à "l"
	else {
		for (long int n = 0; n < l && index + n < l; n++) {
			nom[n] = path[n + index];
		}
		nom[l - index] = '\0';
	}

	return nom;
}

s_file *process_file(char *path, bool doMD5){
	// Structures de manipulation de fichier
	struct stat stats;

	// Lecture de l'état du fichier
	lstat(path, &stats);

	// Fichier courant à scanner
	s_file *parent;
	parent = malloc(sizeof(s_file));

	// Champs du fichier
	if(S_ISREG(stats.st_mode)){
		parent->file_type = REGULAR_FILE;
		parent->file_size = stats.st_size;
		// md5sum
		if (doMD5) {
			unsigned char *buffer;
			buffer = malloc(sizeof(char) * (strlen(path) + 34));
			compute_md5(path, buffer);
			snprintf(parent->md5sum, sizeof(parent->md5sum),"%s", buffer);
			free(buffer);
		}
	}
	else parent->file_type = OTHER_TYPE;

	snprintf(parent->name, sizeof(parent->name), "%s", recuperation_nom(path));
	parent->mod_time = stats.st_mtime;
	parent->next_file = NULL;

	return parent;
}

s_directory *process_dir(char *root_path, bool doMD5) {
	DIR *descripteur;
	struct dirent *dirent = NULL;
	struct stat stats;

	s_directory *root;
	root = malloc(sizeof(s_directory));

	lstat(root_path, &stats);

	// init dir
	snprintf(root->name, sizeof(root->name), "%s", recuperation_nom(root_path));
	root->mod_time = stats.st_mtime;
	root->subdirs  = NULL;
	root->files    = NULL;
	root->next_dir = NULL;

	// Ouverture du répertoire
	descripteur = opendir(root_path);
	if (descripteur == NULL) return NULL; // Impossible d'ouvrir le répertoire

	char *path = (char *)malloc(4096 * sizeof(char));

	// Tant qu'il y a des éléments dans le répertoire
	while((dirent = readdir(descripteur)) != NULL) {
		// on évite de traiter les . et .. (boucle infinie)
		if (strcmp(dirent->d_name, ".") == 0 || strcmp(dirent->d_name, "..") == 0) {
			continue;
		}

		strcpy(path, root_path);
		strcat(path, "/"); strcat(path, dirent->d_name);

		// Lecture impossible -> on passe au suivant & on affiche l'erreur
		if (lstat(path, &stats) == -1) {
			perror("stat");
			continue;
		}

		// Si c'est un dossier
		if (S_ISDIR(stats.st_mode) != 0) {
			s_directory *new = process_dir(path, doMD5);
			append_subdir(new, root);
		}

		// Si c'est un fichier ou autre chose
		else {
			s_file *new = process_file(path, doMD5);
			append_file(new, root);
		}
		

	}

	closedir(descripteur);
	return root;
}
