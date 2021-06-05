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
  while(dir->next_dir != NULL) read_s_directory(dir->next_dir);

  printf("/**********Files of %s*********/ \n",dir->name);
  while(dir->files != NULL)
  {
    printf("%s\n",dir->files->name);
    dir->files = dir->files->next_file;
  }
  printf("\n");

  while(dir->subdirs != NULL)
  {
    printf("/**********Files of %s*********/ \n",dir->subdirs->name);
    while(dir->subdirs->files != NULL)
    {
      printf("%s\n",dir->subdirs->files->name);
      dir->subdirs->files = dir->subdirs->files->next_file;
    }
    printf("\n");
    dir->subdirs = dir->subdirs->next_dir;
  }

}
