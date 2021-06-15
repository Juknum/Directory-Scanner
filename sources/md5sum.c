#include "../headers/md5sum.h"
#define MAX_LEN 4096

int compute_md5(char *path, unsigned char buffer[]) {
	char *return_command = malloc(sizeof(char) * (strlen(path) + 34));  // 32 caractères de md5sum + " " + taille du chemin 
	char *command = malloc(sizeof(char) * (strlen(path) + 10));         // 8 caractères pour "md5sum " + 2 pour les ""

	strcpy(command, "md5sum \""); 
	strcat(command, path);
	strcat(command, "\"");

	FILE * f = popen(command, "r"); // Execute la commande permettant d'obtenir la somme md5 du fichier
	if (!f) {
		printf("Impossible de calculer md5um de %s\n",path);
		free(return_command);
		free(command);
		return -1;
	}

	fgets(return_command, 32, f); // Lecture du fichier sur les 32 premiers caractères (md5sum fait 32 char de long)

	strcpy(buffer, return_command);
	pclose(f);
	free(return_command);
	free(command);
	return 0;
}
