#include "tree.h"

/*---------------------------------------------------------*/

int append_subdir(s_directory *child, s_directory *parent)
{
    //Nécessité d'existences des deux directory child et parent.
    if (!child || !parent)
    {
        return 1;
    }
    
    //Cas trivial : si le dossier parent n'a pas de sous-dossiers
    //alors le premier sous-dossier de parent est child.
    if (!parent->subdirs)
    {
        parent->subdirs = child;
        return 0;
    }
    
    //Cas général
    //1ère étape : parcours de la liste des subdirs de parent jusqu'au dernier élément.
    s_directory * tmp = parent->subdirs;
    while (tmp->next_dir != NULL) {
        tmp = tmp->next_dir;
    }
    //2ème étape : Ajout en queue du nouveau sous dossier child. 
    tmp->next_dir = child;

    return 0;

}
    

/*---------------------------------------------------------*/

int append_file(s_file *child, s_directory *parent)
{
    //Nécessité d'existences des deux directory child et parent.
    if (!child || !parent)
    {
        return 1;
    }

    //Cas trivial : si le dossier parent n'a pas de fichiers
    //alors le premier fichier de parent est child.
    if (!parent->files)
    {
        parent->files = child;
        return 0;
    }
    
    //Cas général
    //1ère étape : parcours de la liste des files de parent jusqu'au dernier élément.
    s_file *tmp = parent->files;
    while (tmp->next_file != NULL) {
        tmp = tmp->next_file;
    }
    //2ème étape : Ajout en queue du nouveau sous dossier child.
    tmp->next_file = child;
  
    return 0;
}

/*---------------------------------------------------------*/

void clear_files(s_directory* parent)
{
    //Nécessité d'existence du directory parent.
    if (parent == NULL)
    {
        return;
    }

    //Parcours de la liste des fichiers de parent
    //Et suppression de ces fichiers un à un.
    s_file * tmp = NULL;
    while (parent->files != NULL)
    {
        tmp = parent->files->next_file;
        free(parent->files);
        parent->files = tmp;
    }
}

/*---------------------------------------------------------*/


void clear_subdirs(s_directory* parent)
{
    //Nécessité d'existence du directory parent.
    if(parent==NULL)
    {
        return;
    }
	
	//1ère étape : Suppression des fichiers du dossier parent.
	clear_files(parent);
	
	//2ème étape : Appel récurcif de la fonction pour les sous-dossiers de parent.
	s_directory* dirs=parent->subdirs;
	s_directory* next_subdir;

	while(dirs!=NULL)
	{
		next_subdir=dirs->next_dir;
		clear_subdirs(dirs);
		dirs=next_subdir;
	}
	free(parent);
}