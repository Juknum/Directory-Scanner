#include <stdio.h>
#include <dirent.h>
#include <errno.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <linux/limits.h>
#include <time.h>

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
	

	FILE *f;
	if (! (f=fopen(path_to_target,"w")) ) return 0;
	
	print_dir(root,""); 
	
	fclose(f);
	return -1;
}




// =======================




void print_file(s_file *file, char *path) {
	if (file==NULL) return;
	
	// Type du fichier
	printf("%d\t",file->file_type);
	
	// Date
	struct tm *tmtime;
	tmtime = localtime(&file->mod_time);
	
	printf("%04d-%02d-%02d-%02d:%02d:%02d\t",tmtime->tm_year+1900,tmtime->tm_mon+1,tmtime->tm_mday,tmtime->tm_hour,tmtime->tm_min,tmtime->tm_sec);
	
	if (file->file_type==REGULAR_FILE) {
		// Taille
		printf("%ld\t",file->file_size);
		
		if (enable_md5) {
			for(int i=0;i<MD5_DIGEST_LENGTH;i++)
				printf("%02x",file->md5sum[i]);
			printf("\t");		
		}
	}
	
	// Chemin
	printf("%s",file->name);
	
	printf("\n");
	
	
	if (file->next_file!=NULL)
		print_file(file->next_file,path); 
}

void print_dir(s_directory *dir,char *path) {
	if(dir==NULL) return; 
	
	printf("%d\t%s\n",DIRECTORY,dir->name);
	
	// Dossiers de même niveau
	print_dir(dir->next_dir,path);
	
	// Fichiers
	print_file(dir->files,path);
	
	// Sous-dossiers
	print_dir(dir->subdirs,path);

}
