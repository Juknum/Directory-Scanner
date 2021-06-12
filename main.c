#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>


int main(int argc, char *argv[]) {

	// La variable statut_md5sum permet de savoir si le calcul des sommes MD5 des fichiers est actif ou non. Elle vaut 1 si activée.
	int statut_md5sum = 0;

	DIR* fichier_sortie = NULL;
	DIR* dossier_analyse = NULL;







	// On scanne tous les arguments du programme avec une boucle et getopt.
	int opt = 0;
	while((opt = getopt(argc, argv, "o:si:")) != -1) {
		switch (opt) {
			case 'o': //Cas option o
			// On essaie d'ouvrir le fichier de sortie en mode lecture, si il est ouvert c'est qu'il existe et qu'il s'agit bien d'un fichier.
				fichier_sortie = opendir(optarg);
					if (fichier_sortie != NULL)
    				{
    					printf("Erreur : l'argument donné avec l'option o n'est pas un fichier.");
    					closedir(fichier_sortie);

    				}
    				else
    				{
    					// argument fichier de sortie valide
 					    printf("C'est un fichier !\n");   		       			
    				}


				break;
				
			case 's': //Cas option s
				// Si l'option s est indiquée, la variable statut_md5sum devient égale à 1.
				statut_md5sum = 1;
				printf("Option s activée : %d\n",statut_md5sum);
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

			default:
				break;
		}
	}
}