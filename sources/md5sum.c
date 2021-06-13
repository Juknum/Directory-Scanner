#include "../headers/md5sum.h"

#define MAX_LEN 2048

int compute_md5(char *path, unsigned char buffer[]) {
	char *return_command = malloc(sizeof(char) * (strlen(path) + 34)); //32 caractères de md5sum + " " + taille du chemin 
	char *command = malloc(sizeof(char) * (strlen(path) + 8)); //8 caractères "md5sum " + taille du chemin 
	
	strcat(command, "md5sum "); 
	strcat(command, path);
	
    FILE * f = popen(command, "r"); //execute la commande permettant d'obtenir la somme md5 du fichier
    if (f==NULL) {
		printf("Impossible de calculer md5um de %s\n",path);
		return -1;
	}
    
    fgets(return_command, MAX_LEN, f);// Lecture du fichier, sur maximum 2048 caractères
    
    char *md5sum = strtok(return_command, " "); //Traite la chaine pour ne récupérer que la somme
	strcat(buffer, md5sum);
	
    pclose(f);
    free(return_command);
    free(command);
	return 0;
}
