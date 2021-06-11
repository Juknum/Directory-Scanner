/**
 * Fonction principale
 * @param argc Nombre d'arguments
 * @param argv Tableau des arguemnts
 */
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../headers/definitions.h"
#include "../headers/scan.h"
#include "../headers/save.h"
#include "../headers/tree.h"




int main(int argc, char *argv[]) {
	char *file, *directory;
	short is_file = 0, is_dir = 0, opt = 0, check_md5 = 0;
	
	while((opt = getopt(argc, argv, "o:si:")) != -1) 
	{
		switch (opt) 
		{
			case 'o': //obtenir le nom du fichier de sauvegarde
				file = malloc(sizeof(char) * strlen(optarg));
				strcpy(file,optarg);
				is_file = 1;
				printf("-> saving in file %s\n", file);
				break;
				
			case 's'://activation du calcul des sommes MD5
				check_md5 = 1;//Vaut 1 si la somme doit etre calculé, 0 sinon
				printf("-> activating MD5 calculus \n");
				break;

			case 'i'://obtenir le répertoire à analyser
				;
				DIR *test_dir = opendir(optarg);//Vérifie l'existence du répertoire
				if (!test_dir) 
				{
					printf("%s is not a valid path\n", optarg);
					return 1;
				}
				closedir(test_dir);
				directory = malloc(sizeof(char) * strlen(optarg));
				strcpy(directory,optarg);
				is_dir = 1;
				printf("-> analysing directory: %s\n", directory);
				break;

			default:
				break;
		}
	}
	if (is_file == 0)//Si aucun fichier n'a été précisé, création du fichier de sauvegarde
	{
		file = malloc(sizeof(char) * 38);
		DIR *dir = opendir("filescanner");//Vérifie l'existence du répertoire
		if (!dir) 
		{
			mkdir("filescanner",777);//Si il n'existe pas, le crée
		}
		closedir(dir);
		strcpy(file,"filescanner/");
		
		char today_time[20];//Récupère la date complète
		time_t timestamp;
		time(&timestamp);
		struct tm *info = localtime(&timestamp);

		strftime(today_time, 20, "%Y-%m-%d-%H:%M:%S", info);
		strcat(file, today_time); strcat(file,".scan");
		
		FILE *f = NULL;
		f = fopen(file, "a");//Crée le fichier
		if (f != NULL)
		{
			printf("-> saving in file %s\n", file);
			fclose(f);
		}else
		{
			printf("can't create %s\n", file);
			return 1;
		}
	}
	if (is_dir == 0)//Si aucun répertoire n'a été précisé, analyse du répertoire courant "."
	{
		directory = malloc(sizeof(char) * strlen("."));
		strcpy(directory,".");
		printf("-> analysing directory: %s\n",directory);
	}

	s_directory * parent = process_dir("dossier_test","dossier_test");
	printf("Fin scan\n");

	save_to_file(parent, file, 1, "..");
	printf("Fin sauvegarde\n");

	clear_subdirs(parent);


	//programme(file,directory,check_md5)
	free(file); free(directory);
	return 0;
}

// /!\ouvrir le fichier de sauvegarde en mode "a"
