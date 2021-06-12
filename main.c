#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>

#include <linux/limits.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

#include "types.h"
#include "scan.h"
#include "test.h"
#include "save.h"
#include "tree.h"


int enable_md5 = 0;
// La variable globale enable_md5 permet de savoir si le calcul des sommes MD5 des fichiers est actif ou non. Elle vaut 1 si activée.

int main(int argc, char *argv[]) {
	
	//
	char in_path[PATH_MAX+1] = ".";


// Nom du fichier de sortie par défaut
	time_t t;
	time(&t);
	struct tm *tmtime;
	tmtime = localtime(&t);
	char *out_file = malloc(sizeof(char)*PATH_MAX+1);
	snprintf(out_file,PATH_MAX+1,"%s/.filescanner/%04d-%02d-%02d:%02d:%02d:%02d.scan",getenv("HOME"),tmtime->tm_year+1900,tmtime->tm_mon+1,tmtime->tm_mday,tmtime->tm_hour,tmtime->tm_min,tmtime->tm_sec);


// Initialisation des pointeurs pour la vérification des arguments
	DIR* fichier_sortie = NULL;
	DIR* dossier_analyse = NULL;



	// On scanne tous les arguments du programme avec une boucle et getopt.
	int opt = 0;
	while((opt = getopt(argc, argv, "o:si:")) != -1) {
		switch (opt) {

			case 'o': //Cas option -o
			
			// On essaie d'ouvrir le fichier de sortie en mode lecture.
			// Si il est ouvert, c'est qu'il existe et qu'il s'agit bien d'un fichier.

				fichier_sortie = opendir(optarg);
					if (fichier_sortie != NULL)
    				{
    					printf("Erreur : l'argument donné avec l'option o n'est pas un fichier.");
    					closedir(fichier_sortie);

    				}
    				else
    				{
    					// L'argument fichier de sortie valide, on copie l'argument dans out_file.
 					    strncpy(out_file,optarg,PATH_MAX); 		       			
    				}


				break;
				
			case 's': //Cas option -s
				// Si l'option s est indiquée, la variable globale enable_md5 devient égale à 1.
				enable_md5 = 1;

				break;

			case 'i': //Cas option i
					dossier_analyse = opendir(optarg);
					if (dossier_analyse != NULL)
					{
						printf("C'est bien un dossier !\n");
					}
					else
					{
						printf("Ce n'est PAS un dossier !\n");
					}
				
				break;
		}

		// Scanner le répertoire d'entrée récursivement
		s_directory *root_dir = process_dir(in_path);
		
		if(root_dir==NULL) {
		printf("Impossible de scanner le répertoire %s\n",in_path);
		return 1;
		}
		printf("Scan terminé!\n");
	
		// Sauvegarder les résultats du scan
		if (save_to_file(root_dir,out_file)==0) {
		printf("Échec de l'enregistrement dans le fichier %s\n",out_file);
		return 1;
		}
		printf("Fichier enregistré dans %s\n",out_file);
	
	
		// Libérer les éléments alloués dans la mémoire
		free(out_file);
		clear_files(root_dir);
		clear_subdirs(root_dir);
		free(root_dir);
		return 0;
		}

	}