#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <errno.h>
#include <unistd.h>
#include <pwd.h>
#include "main.h"
#include "scan.h"
#include "save.h"
#include "tree.h"
#include "debug.h"

// activation du calcul md5
int comp_md5=0;
// nom du fichier dans lequel faire la sauvegarde
char save_file_name[PATH_MAX+1]="\0";

int main(int argc, char** argv){
	char* root=".";
	int cmpt=1;
	if(argc>=2){
		while(argv[cmpt]!=NULL){
			//test option -o
			//spécifie le fichier cible
			if(strcmp(argv[cmpt],"-o")==0){
				strcpy(save_file_name,argv[cmpt+1]);
				cmpt=cmpt+2;
				continue;
			}
			//test option -s
			//activation du calcul md5
			if(strcmp(argv[cmpt],"-s")==0){
				comp_md5=1;
				cmpt=cmpt+1;
				continue;
			}
			//test option -i
			//spécifie le répertoire source
			if(strcmp(argv[cmpt],"-i")==0){
				//vérification de l'existence du répertoire
				struct stat stat_source;
				if(stat(argv[cmpt+1],&stat_source)!=0){
					fprintf(stderr,"le répertoire source n'existe pas\n");
					return -1;
				}
				root=argv[cmpt+1];
				cmpt=cmpt+2;
				continue;
			}
			fprintf(stderr,"erreur d'usage du programme\n");
			return -1;
		}
	}
	if(get_save_file_name(save_file_name)!=0)
		return -1;
	debug("beforeprocessdir");
	s_directory* struct_root;
	// création de la structure
	struct_root=process_dir(root);
	debug("beforesave_to_db");
	// sauvegarde de la structure dans la base de données
	save_to_db(struct_root);
	debug("beforesave_to_file");
	// sauvegarde de la structure dans le fichier
	save_to_file(struct_root,save_file_name);
	debug("beforeclear_subdirs");
	// libération de la mémoire
	clear_subdirs(struct_root);
	return 0;
}

int get_compute_md5(){
	// permet de savoir si le calcul md5 est activé ou pas
	return comp_md5;
}

int get_save_file_name(char* file_name){
	// construction du nom du fichier de sauvegarde
	if(file_name[0]!='\0'){
		return 0;
	}
	// test si le répertoire filescanner existe
	struct passwd* pw=getpwuid(getuid());
	sprintf(file_name,"%s/%s",pw->pw_dir,FILESCANNER_PATH);
	struct stat stat_filescanner;
	if(stat(file_name,&stat_filescanner)==0){
		if(S_ISDIR(stat_filescanner.st_mode)==0){
			fprintf(stderr,"Il existe un fichier %s\n",file_name);
			return -1;
		}
	}else{
		// créer le répertoire
		if(mkdir(file_name,S_IRWXU)!=0){
			fprintf(stderr,"erreur de création du répertoire %s: errno=%d\n", FILESCANNER_PATH,errno);
			return -1;
		}
	}
	// recherche de la date/heure
	time_t now;
	time(&now);
	struct tm* local=localtime(&now);
	sprintf(file_name,"%s/%s/%04d-%02d-%02d-%02d:%02d:%02d.scan",pw->pw_dir,FILESCANNER_PATH,local->tm_year+1900,
			local->tm_mon+1,local->tm_mday,local->tm_hour,local->tm_min,local->tm_sec);
	debug("file_name: %s",file_name);
	return 0;
}
