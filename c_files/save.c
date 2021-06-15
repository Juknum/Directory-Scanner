#include "../h_fichiers/save.h"
#include <stdio.h>

// Cette fonction sert à enregister dans une fichier texte
int save_to_file(s_directory *root, char *path_txt, bool md5)
{
	FILE *f = NULL;
	if(strcmp(path_txt,"stdout")==0)
	{
		f = stdout;
	} 
	else if (strcmp(path_txt,getenv("HOME")) == 0)
	{
		bool isCreated = true;
		isCreated = mkdir(strcat(path_txt,"/.fichierscanner/"),0755);
		if(!isCreated) 
		{
			printf("The file was not created\n");
		}

		char buff[100];
		time_t now = time (NULL);
		struct tm tm_now = *localtime (&now); // On récupère la date et l'heure
		strftime(buff, 50, "%Y-%m-%d-%H:%M:%S",&tm_now); // On initialise le format

		strcat(path_txt,buff);
		strcat(path_txt,".scan");
		path_txt[strlen(path_txt)] = '\0';
		printf("Enregistrement dans le path : %s\n",path_txt);
		f = fopen(path_txt, "w");
		if(!f) 
		{
			f = fopen(path_txt, "a");
		}
	}
	else
	{
		f = fopen(path_txt, "w");
		if(!f) 
		{
			f = fopen(path_txt, "a");
		}
	}


	if (f != NULL) 
	{
		ecrire_dirs(root, f,0, md5);
		fclose(f);
	} 
	else 
	{
		fprintf(stderr,"Impossible d'ouvrir le fichier\n");
	}
	free(path_txt);
	return 0;
}

// Cette fonction sert à écrire les fichiers
void ecrire_fichiers(s_file* fichiers,FILE* f, int tabs, bool md5)
{
    char* buff = NULL;
    if(fichiers != NULL )
    {
        if(fichiers->file_type !=DIRECTORY)
        {
            buff = calloc(sizeof(char),100);
            print_tabs(tabs, f);

            fprintf(f,"%d ",fichiers->file_type);
            strftime(buff, 100, "%d/%m/%Y %H:%M:%S",localtime(&fichiers->mod_time) );
            fprintf(f,"%s %lu ",buff,fichiers->file_size);
            if(md5)
            {
                print_md5sum(fichiers->md5sum, f);
                fprintf(f," ");
            }

            fprintf(f,"%s\n",fichiers->name);
        }
        free(buff);
        ecrire_fichiers(fichiers->next_file, f, tabs, md5);
    }

}
// Cette fonction sert à écrire les directory
void ecrire_dirs(s_directory* dirs, FILE* f, int tabs, bool md5)
{
	char* buff = NULL;
	if(dirs != NULL)
	{
		buff = calloc(sizeof(char),100);
		print_tabs(tabs, f);
		fprintf(f,"0 ");
		strftime(buff, 100, "%d/%m/%Y %H:%M:%S",localtime(&dirs->mod_time));
		fprintf(f,"%s %s\n",buff,dirs->name);

		free(buff);
		ecrire_fichiers(dirs->fichiers,f, tabs+1,md5);
		ecrire_dirs(dirs->subdirs,f,tabs+1,md5);
		ecrire_dirs(dirs->next_dir,f,tabs,md5);
	} 
	else
	{
		print_tabs(tabs, f);
		fprintf(f,"\n");
	}
}

// Cette fonction sert à afficher les tabulations
void print_tabs(int tabs,FILE* f)
{
    for(int i=0;i<tabs;i++)
    {
        fprintf(f,"->  ");
    }
}

// Cette fonction sert à afficher la somme MD5
void print_md5sum(unsigned char buff[], FILE* f)
{
    for(int n=0; n<MD5_DIGEST_LENGTH; n++)
    {
    	fprintf(f,"%02x", buff[n]);
    }
}
