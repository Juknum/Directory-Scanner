#include "../h_files/structures.h"
#include "../h_files/save.h"
#include "../h_files/md5sum.h"
#include "../h_files/tree.h"
#include "../h_files/scan.h"

int main(int argc, char* argv[]){
	int opt = 0;
	char* path = NULL;
	char* dirPath = NULL;
	bool BoolMD5 = false;
	struct option mes_options[] = {
	{.name="save-file",.has_arg=1,.flag=0,.val='o'},
	{.name="BoolMD5",.has_arg=0,.flag=0,.val='s'},
	{.name="directory",.has_arg=1,.flag=0,.val='i'},
	{.name=0,.has_arg=0,.flag=0,.val=0},};  

	while((opt = getopt_long(argc, argv, "o:shi:", mes_options, NULL)) != -1) 
	{
		switch (opt) // On analyse les paramètre entrée par l'utilisateur
		{
		case 'o': //Parametrage du -o avec un argument obligatoire
		  if(optarg[0] != '-')
		  {
				printf("Le fichier où cela va être enregistré est : %s\n",optarg);
				path = calloc(sizeof(char),strlen(optarg)+1);
				path = strcpy(path, optarg);
		  } else{
				fprintf(stderr,"L'argument n'est pas valide !\n");
				return EXIT_FAILURE;
		  }
		  break;

		case 's': //Parametrage du -s sans argument
			printf("La somme MD5 va être calculée\n");
			BoolMD5 = true;
		  break;

		case 'i': //Parametrage du -i avec un argument obligatoire
		  if(optarg[0] != '-')
		  {
				printf("Le dossié évalué est : %s\n",optarg);
				dirPath = calloc(sizeof(char),strlen(optarg)+1);
				dirPath = strcpy(dirPath, optarg);
		  }
		  else
		  {
				fprintf(stderr,"L'argument n'est pas valide !\n");
				return EXIT_FAILURE;
		  }
		  break;
		}
	}

	if(!dirPath)
	{
		dirPath = calloc(sizeof(char),2);
		dirPath[0] = '.';
		dirPath[1] = '\0';
	}

	if(!path)
	{
		path = calloc(sizeof(char),strlen("/.filescanner/yyyy-MM-dd-hh:mm:ss.scan")+strlen(getenv("HOME"))+1);
		strcpy(path,getenv("HOME"));
	}

	if(BoolMD5)
	{
		printf("Somme MD5 calculée...\n");
	}

	s_directory* test = process_dir(dirPath, BoolMD5); // On analyse le directory

	save_to_file(test,path,BoolMD5); // On enregistre ceci dans un fichier texte

	clear_subdirs(test); // On libere ensuite la mémoire

	free(test);

	return EXIT_SUCCESS;
}
