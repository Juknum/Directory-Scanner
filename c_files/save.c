#include "../include/save.h"
#include <stdio.h>

int save_to_file(s_directory *root, char *path_to_target){
    bool isCreated = true;
    //char* buffer = calloc(sizeof(char),100);
    isCreated = mkdir("~/.filescanner",0755);
    if(!isCreated) fprintf(stderr,"le fichier n'a pas été créé");
    FILE *fichier = NULL;
    if(strcmp(path_to_target,"stdout")==0){
        fichier = stdout;
    } else {
        fichier = fopen("~/lol.txt", "w");
    }


    if (fichier != NULL) {
        printf("possible d'ouvrir le fichier sauvegharde.txt\n");

        fprintf(fichier,"0 ");
        //strftime(buffer, 100, "%d/%m/%Y %H:%M:%S",localtime(&(root->mod_time)) );
        //fprintf(fichier,"%s %s\n",buffer,root->name);
        //free(buffer);
        write_files(root->files, fichier,1);

        write_directories(root->subdirs, fichier,1);

        fclose(fichier);
    } else {
        // On affiche un message d'erreur
        fprintf(stderr,"Impossible d'ouvrir le fichier\n");
    }
    exit(EXIT_SUCCESS);

}

void write_files(s_file* files,FILE* fichier, int tabs){
    char* buffer = NULL;
    if(files != NULL ){
        if(files->file_type !=DIRECTORY){
            buffer = calloc(sizeof(char),100);
            print_tabs(tabs, fichier);

            fprintf(fichier,"%d ",files->file_type);
            strftime(buffer, 100, "%d/%m/%Y %H:%M:%S",localtime(&files->mod_time) );
            fprintf(fichier,"%s %lu ",buffer,files->file_size);
            print_md5sum(files->md5sum, fichier);
            fprintf(fichier," %s\n",files->name);
        }
        free(buffer);
        write_files(files->next_file, fichier, tabs);
    }

}

void write_directories(s_directory* directories, FILE* fichier, int tabs){
    char* buffer = NULL;
    if(directories != NULL){
        buffer = calloc(sizeof(char),100);
        print_tabs(tabs, fichier);
        fprintf(fichier,"0 ");
        strftime(buffer, 100, "%d/%m/%Y %H:%M:%S",localtime(&directories->mod_time) );
        fprintf(fichier,"%s %s\n",buffer,directories->name);

        free(buffer);
        write_files(directories->files,fichier, tabs+1);
        write_directories(directories->subdirs,fichier,tabs+1);
        write_directories(directories->next_dir,fichier,tabs);
    } else{
        print_tabs(tabs, fichier);
        printf("------------------------------\n");
    }
}

void print_tabs(int tabs,FILE* fichier){
    for(int i=0;i<tabs;i++){
        fprintf(fichier,"|  ");
    }
}

void print_md5sum(unsigned char buffer[], FILE* fichier){
    for(int n=0; n<MD5_DIGEST_LENGTH; n++) fprintf(fichier,"%02x", buffer[n]);
}
