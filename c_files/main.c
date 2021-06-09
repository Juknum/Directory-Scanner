#include "../include/structures.h"
#include "../include/save.h"
#include "../include/md5sum.h"
#include "../include/tree.h"
#include "../include/scan.h"

void read_s_directory(s_directory* dir);

int main(int argc, char* argv[]){
    if(argc < 2)
    {
      fprintf(stderr,"Not enough argument to the function\n");
      return EXIT_FAILURE;
    }

    s_directory* test = process_dir(argv[1]);
    if(test) read_s_directory(test);

    clear_subdirs(test);
    if(!test->subdirs)
    {
      free(test);
      printf("Successefully cleared subdirs\n");
    }

    return EXIT_SUCCESS;
}

/**********************************************************************************************/

void read_s_directory(s_directory* dir)
{
    char buffer[100];

    printf("/**********Files of %s*********/ \n",dir->name);
    while(dir->files != NULL)
    {
      printf("%s\n",dir->files->name);
      strftime(buffer, 50, "%d/%m/%Y %H:%M:%S",localtime(&(dir->files->mod_time)) );
      printf("%s\n",buffer);
      printf("%ld\n",dir->files->file_size);
      printf("%s\n",dir->files->md5sum);
      dir->files = dir->files->next_file;
    }
    printf("\n");

    while(dir->subdirs)
    {
      read_s_directory(dir->subdirs);
      save_to_file(dir,"./filescanner");
      dir->subdirs = dir->subdirs->next_dir;
    }
}
