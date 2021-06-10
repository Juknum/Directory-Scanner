#include "../include/structures.h"
#include "../include/save.h"
#include "../include/md5sum.h"
#include "../include/tree.h"
#include "../include/scan.h"
#include <string.h>

void read_s_directory(s_directory* dir);

int main(int argc, char* argv[]){
    int opt =0;
    char* path = NULL;
    char* dirPath = NULL;
    bool evaluate_md5 = false;
    struct option my_opts[] = {
      {.name="save-file",.has_arg=1,.flag=0,.val='o'},
      {.name="evaluate_md5",.has_arg=0,.flag=0,.val='s'},
      {.name="directory",.has_arg=1,.flag=0,.val='i'},
      {.name=0,.has_arg=0,.flag=0,.val=0}, // last element must be zero
    };

    while((opt = getopt_long(argc, argv, "o:si:", my_opts, NULL)) != -1) {
      switch (opt) {
        case 'o':
          if(optarg[0] != '-'){
            printf("The file where the arborescence will be saved is : %s\n",optarg);
            path = calloc(sizeof(char),strlen(optarg)+1);
            path = strcpy(path, optarg);
          } else{
            fprintf(stderr,"Argument is invalid!\n");
            return EXIT_FAILURE;
          }
          break;

        case 's':
          printf("md5sum will be calculated\n");
          evaluate_md5 = true;
          break;

        case 'i':
          if(optarg[0] != '-'){
            printf("The directory evaluated is : %s\n",optarg);
            dirPath = calloc(sizeof(char),strlen(optarg)+1);
            dirPath = strcpy(dirPath, optarg);
          } else{
            fprintf(stderr,"Argument is invalid!\n");
            return EXIT_FAILURE;
          }
          break;
        case '?':
          fprintf(stderr,"Unknown option!\n");
          return EXIT_FAILURE;
          break;
      }
    }

    if(!dirPath){
      dirPath = calloc(sizeof(char),2);
      dirPath[0] = '.';
      dirPath[1] = '\0';
    }

    if(!path){
      path = calloc(sizeof(char),strlen("/.filescanner/yyyy-MM-dd-hh:mm:ss.scan")+strlen(getenv("HOME"))+1);
      strcpy(path,getenv("HOME"));
    }

    if(evaluate_md5){
      printf("Evaluation of md5sum...\n");
    }

    s_directory* test = process_dir(dirPath, evaluate_md5);

    save_to_file(test,path,evaluate_md5);

    //if(test) read_s_directory(test);
    clear_subdirs(test);

    if(!test->subdirs && !test->files) printf("Successefully cleared subdirs\n");
    free(test);

    return EXIT_SUCCESS;
}

/**********************************************************************************************/

void read_s_directory(s_directory* dir)
{


    printf("/**********Files of %s*********/ \n",dir->name);
    while(dir->files != NULL)
    {
      //char buffer[100];
      printf("%s\n",dir->files->name);
      /*strftime(buffer, 50, "%d/%m/%Y %H:%M:%S",localtime(&(dir->files->mod_time)) );
      printf("%s\n",buffer);
      printf("%ld\n",dir->files->file_size);*/
      dir->files = dir->files->next_file;
    }
    printf("\n");

    while(dir->subdirs)
    {
      read_s_directory(dir->subdirs);
      dir->subdirs = dir->subdirs->next_dir;
    }
}
