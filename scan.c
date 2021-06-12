#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <linux/limits.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <errno.h>
#include <libgen.h>

#include "scan.h"
#include "tree.h"
#include "md5sum.h"

extern int enable_md5;

s_directory *process_dir(char *path) {
	DIR *d = opendir(path);
	
	// Créer la structure stat pour obtenir des informations sur le répertoire
	struct stat dirstat;
	lstat(path,&dirstat);
	
	// Créer la structure s_directory du répertoire et commencer à la remplir
	s_directory *dirstruct = malloc(sizeof(s_directory));
	strcpy(dirstruct->name,basename(path));
	dirstruct->mod_time = dirstat.st_mtime;
	dirstruct->subdirs = NULL;
	dirstruct->files = NULL;
	dirstruct->next_dir = NULL;
	
	// Parcourir le contenu du répertoire si celui-ci est lisible
	if (d==NULL)
		printf("Impossible de scanner le contenu du répertoire '%s' (erreur %d).\n",path,errno);
	else {
		struct dirent *entry = readdir(d);
		while (entry!=NULL) {
			char entrypath[PATH_MAX];
			snprintf(entrypath,PATH_MAX,"%s/%s",path,entry->d_name);
			
			// Créer une structure stat de l'entrée pour vérifier si celle-ci est un fichier ou un répertoire
			struct stat entrystat;
			lstat(entrypath,&entrystat);
			
			// Chercher des répertoires/fichiers dans ce répertoire (sauf "." et "..")
			if ( strcmp(entry->d_name,".")!=0 && strcmp(entry->d_name,"..")!=0 ) {
			
				// Le fichier est un répertoire
				if (S_ISDIR(entrystat.st_mode)) {
					s_directory *subdirstruct = process_dir(entrypath);
					append_subdir(subdirstruct,dirstruct);
				}	
				// Le fichier n'est pas un répertoire
				else {
					s_file *filestruct = process_file(entrypath);
					append_file(filestruct,dirstruct);
				}
			}
			entry = readdir(d); // Passer à l'entrée suivante
		}
	}
	
	closedir(d);
	return dirstruct;
}



s_file *process_file(char *path) {
	
	// Créer une structure stat pour obtenir les informations sur le fichier
	struct stat filestat;
	lstat(path,&filestat);
	
	// Créer la structure s_file et remplir les informations
	s_file *filestruct = malloc(sizeof(s_file));
	strcpy(filestruct->name,basename(path));
	filestruct->mod_time = filestat.st_mtime;
	filestruct->file_size = (uint64_t) filestat.st_size;
	filestruct->next_file = NULL;
	
	// MD5
	if (enable_md5) {
		unsigned char md5[MD5_DIGEST_LENGTH];
		if (compute_md5(path,md5)==-1)
			memcpy(filestruct->md5sum,md5,sizeof(unsigned char));
	}

	// Type du fichier
	if (S_ISREG(filestat.st_mode))
		filestruct->file_type = REGULAR_FILE;
	else
		filestruct->file_type = OTHER_TYPE;

	return filestruct;
}

