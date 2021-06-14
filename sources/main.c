#include "../headers/definitions.h"
#include "../headers/scan.h"
#include "../headers/save.h"

/**
 * Fonction principale: gère les options, controle les arguments puis appelle les fonctions scan et save
 * @author Antoine
 * @param argc Nombre d'arguments
 * @param argv Tableau des arguemnts
 */
int main(int argc, char *argv[]) {
	char *file, *directory;
	short is_file = 0, is_dir = 0, opt = 0;
	bool check_md5 = false;
		
	while((opt = getopt(argc, argv, "i:so")) != -1) {
		switch (opt) {
			// obtenir le nom du fichier de sauvegarde
			case 'o': 
				file = malloc(sizeof(char) * strlen(optarg));
				strcpy(file,optarg);
				is_file = 1;
				printf("-> saving in file %s\n", file);
				break;
				
			// activation du calcul des sommes MD5
			case 's': 
				check_md5 = true; // Vaut vrai si la somme doit etre calculé, faux sinon
				printf("-> activating MD5 sum\n");
				break;

			// obtenir le répertoire à analyser
			case 'i':; // ; -> fix de: "error: a label can only be part of a statement and a declaration is not a statement"
				
				// Vérifie l'existence du répertoire
				DIR *test_dir = opendir(optarg);
				if (!test_dir) {
					printf("%s is not a valid path\n", optarg);
					return 1;
				}
				closedir(test_dir);
				directory = malloc(sizeof(char) * strlen(optarg));
				strcpy(directory,optarg);
				is_dir = 1;
				printf("-> analysing directory: %s\n", directory);
				break;

			// options non définie: 
			default:
				printf("\nOPTIONS:\n\t-o\t:\tSave file location, default: ~/.filescanner/year-month-day-H:M:S.scan\n\t-s\t:\tActivate MD5 sum, disabled by default\n\t-i\t:\tDirectory to scan, \".\" by default.\n\n");
				return 0;
		}
	}

	// Si aucun fichier n'a été précisé, création du fichier de sauvegarde
	if (is_file == 0) {
		file = malloc(sizeof(char) * 38);
		DIR *dir = opendir(".filescanner"); // Vérifie l'existence du répertoire
		if (!dir) mkdir(".filescanner", 0755); // Si il n'existe pas, le crée
		closedir(dir);
		strcpy(file,".filescanner/");
		
		char today_time[20]; // Récupère la date complète
		time_t timestamp;
		time(&timestamp);
		struct tm *info = localtime(&timestamp);

		strftime(today_time, 20, "%Y-%m-%d-%H:%M:%S", info);
		strcat(file, today_time); strcat(file,".scan");
		
		FILE *f = NULL;
		f = fopen(file, "a"); // Crée le fichier
		if (f != NULL) {
			printf("-> saving in file %s\n", file);
			fclose(f);
		}
		else {
			printf("can't create %s\n", file);
			return 1;
		}
	}

	// Si aucun répertoire n'a été précisé, analyse du répertoire courant "."
	if (is_dir == 0) {
		directory = malloc(sizeof(char) * strlen("."));
		strcpy(directory,".");
		printf("-> analysing directory: %s\n",directory);
	}

	s_directory * parent = process_dir(directory, check_md5);
	printf("Scan success\n");


	save_to_file(parent, file, 0, directory, check_md5);
	printf("Save success\n");

	//clear_subdirs(parent);

	//programme(file,directory,check_md5)
	free(file); free(directory);
	return 0;
}
