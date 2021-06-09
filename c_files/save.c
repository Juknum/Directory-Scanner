#include "../include/save.h"

int save_to_file(s_directory *root, char *path_to_target){
    bool isCreated = true;
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
        fprintf(fichier,"0\t%ld\t%s\n",root->mod_time,root->name);

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
    if(files != NULL){
        print_tabs(tabs, fichier);
        fprintf(fichier,"%d\t%ld\t%lu\t%s\t%s\n",files->file_type,files->mod_time,files->file_size,files->md5sum,files->name);
        write_files(files->next_file, fichier, tabs);
    }
}

void write_directories(s_directory* directories, FILE* fichier, int tabs){
    if(directories != NULL){
        print_tabs(tabs, fichier);
        fprintf(fichier,"0\t%ld\t%s\n",directories->mod_time,directories->name);
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
