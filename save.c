#include <stdio.h>
#include <dirent.h>
#include <errno.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <linux/limits.h>
#include <time.h>
#include <string.h>

#include "save.h"

extern int enable_md5;

int save_to_file(s_directory *root, char *path_to_target) {

	char *default_dir = malloc((PATH_MAX+1)*sizeof(char));
	snprintf(default_dir,PATH_MAX,"%s/.filescanner/",getenv("HOME")); // Impossible d'utiliser directment ~ pour home

	// Créer le dossier de sortie par défaut s'il n'existe pas
	DIR* d = opendir(default_dir);
	if (d!=NULL)
		closedir(d);
	else if (ENOENT == errno)
		mkdir(default_dir,0755);
	free(default_dir);
	

	// Enregistrer l'arborescence au format texte dans le fichier de sortie
	FILE *f;
	if (! (f=fopen(path_to_target,"w")) ) return 0;
	print_dir(root,"",f);
	fclose(f);
	return -1;
}

/* Écrire des lignes un fichier et ses fichiers suivants dans le fichier de sortie
	file: structure fichier à écrire
	path: chemin actuel
	of: fichier de sortie ouvert en écriture
*/
void print_file(s_file *file, char *path, FILE *of) {
	if (file==NULL) return;
	
	// Construire la chaîne du chemin vers le fichier
	char newpath[strlen(path)+strlen(file->name)+1];
	snprintf(newpath,strlen(path)+strlen(file->name)+2,"%s%s",path,file->name);
	
	// Type du fichier
	fprintf(of,"%d\t",file->file_type);
	
	// Date
	struct tm *tmtime;
	tmtime = localtime(&file->mod_time);
	
	fprintf(of,"%04d-%02d-%02d-%02d:%02d:%02d\t",tmtime->tm_year+1900,tmtime->tm_mon+1,tmtime->tm_mday,tmtime->tm_hour,tmtime->tm_min,tmtime->tm_sec);
	
	if (file->file_type==REGULAR_FILE) {
		// Taille
		fprintf(of,"%ld\t",file->file_size);
		
		if (enable_md5) {
			for(int i=0;i<MD5_DIGEST_LENGTH;i++)
				fprintf(of,"%02x",file->md5sum[i]);
			fprintf(of,"\t");		
		}
	}
	
	// Chemin
	fprintf(of,"%s\n",newpath);
	
	// Afficher le prochain fichier
	if (file->next_file!=NULL)
		print_file(file->next_file,path,of); 
}


/* Écrire une ligne pour un répertoire ainsi que tout son contenu récursivement dans le fichier de sortie
	dir: structure répertoire à écrire 
	path: chemin actuel
	of: fichier de sortie
*/
void print_dir(s_directory *dir,char *path, FILE *of) {
	if(dir==NULL) return;
	
	// Construire la chaîne du chemin vers le répertoire
	char newpath[strlen(path)+strlen(dir->name)+1];
	snprintf(newpath,strlen(path)+strlen(dir->name)+3,"%s%s/",path,dir->name);
	
	// Type
	fprintf(of,"%d\t",DIRECTORY);
	
	// Date
	struct tm *tmtime;
	tmtime = localtime(&dir->mod_time);
	
	fprintf(of,"%04d-%02d-%02d-%02d:%02d:%02d\t",tmtime->tm_year+1900,tmtime->tm_mon+1,tmtime->tm_mday,tmtime->tm_hour,tmtime->tm_min,tmtime->tm_sec);
	
	// Chemin
	fprintf(of,"%s\n",newpath);
	
	// Afficher les répertoires de même niveau
	print_dir(dir->next_dir,newpath,of);
	
	// Afficher les fichiers
	print_file(dir->files,newpath,of);
	
	// Afficher les Sous-dossiers
	print_dir(dir->subdirs,newpath,of);

}
