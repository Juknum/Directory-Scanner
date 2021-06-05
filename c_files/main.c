#include "../include/structures.h"
#include "../include/save.h"
#include "../include/md5sum.h"
#include "../include/tree.h"
#include "../include/scan.h"

void read_s_directory(s_directory* dir);

int main(int argc, char* argv[]){

    s_directory* test = process_dir(argv[1]);

    if(test) read_s_directory(test);

    free(test);
    return EXIT_SUCCESS;
}

/**********************************************************************************************/

void read_s_directory(s_directory* dir)
{
    printf("/**********Files of %s*********/ \n",dir->name);
    while(dir->files != NULL)
    {
      printf("%s\n",dir->files->name);
      dir->files = dir->files->next_file;
    }
    printf("\n");

    while(dir->subdirs)
    {
      read_s_directory(dir->subdirs);
      dir->subdirs = dir->subdirs->next_dir;
    }
}
