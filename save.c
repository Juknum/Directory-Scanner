
#include<time.h>
#include "save.h"
#define BUFFER_SIZE 150


int save_to_file(s_directory *root, char *path_to_target){
    
        save_dir(root,path_to_target);
        
        s_file *tmp = root->files;
        while(tmp != NULL)
        {
                if(tmp->file_type==REGULAR_FILE){
                        save_reg_file(tmp,path_to_target);
                }

                if(tmp->file_type==OTHER_TYPE){
                        save_oth_type(tmp,path_to_target);
                }
                
                tmp = tmp->next_file;

        }
        if(root->subdirs!=NULL){
                save_to_file(root->subdirs,path_to_target);
        }
        if(root->next_dir!=NULL){
                save_to_file(root->next_dir,path_to_target);
        }


        return EXIT_SUCCESS;



}



void save_reg_file(s_file *file,char *path_to_target){

        struct tm *mod_time;
        mod_time=localtime(&file->mod_time);
        FILE *save_file =fopen(path_to_target,"a");
        fprintf(save_file,"1\t%ld\t%02d/%02d/%04d %02d:%02d\tMD5\t%s\n",file->file_size,mod_time->tm_mday,mod_time->tm_mon+1,mod_time->tm_year+1900,mod_time->tm_hour,mod_time->tm_min,file->name);
        fclose(save_file);
     


/*
1 est le code de REGULAR_FILE;
date est la date comme définie pour le dossier;
taille est la taille en octets du fichier;
MD5 est la somme MD5 du fichier en représentation hexadécimale;
chemin est le chemin complet vers le fichier depuis la racine du scan. Pour les fichiers, il n'y a pas de / à la fin du chemin
*/
}

void save_oth_type(s_file *file,char *path_to_target){

       
         struct tm *mod_time;
        mod_time=localtime(&file->mod_time);
        FILE *save_file =fopen(path_to_target,"a");
    
        fprintf(save_file,"2\t%s\t%02d/%02d/%04d %02d:%02d\n",file->name,mod_time->tm_mday,mod_time->tm_mon+1,mod_time->tm_year+1900,mod_time->tm_hour,mod_time->tm_min);
        fclose(save_file);
       
}
void save_dir(s_directory *dir,char *path_to_target){
    
      struct tm *mod_time;
      mod_time=localtime(&dir->mod_time);
      FILE *save_file =fopen(path_to_target,"a");
      fprintf(save_file,"0\t%02d/%02d/%04d %02d:%02d\t%s/\n",mod_time->tm_mday,mod_time->tm_mon+1,mod_time->tm_year+1900,mod_time->tm_hour,mod_time->tm_min,dir->name);
      
      fclose(save_file);
        

}



