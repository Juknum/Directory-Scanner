#include "../include/structures.h"
#include "../include/save.h"
#include "../include/md5sum.h"
#include "../include/tree.h"
#include "../include/scan.h"



int main(int argc, char* argv[]){

    s_directory* test = process_dir(argv[1]);

      while(test->files != NULL)
      {
        printf("file name : %s\n",test->files->name);
        test->files = test->files->next_file;
      }

      printf("\nsubdir name : %s\n",test->subdirs->name);

      while(test->subdirs->files != NULL)
      {
        printf("name : %s\n",test->subdirs->files->name);
        test->subdirs->files = test->subdirs->files->next_file;
      }


    free(test);
    return EXIT_SUCCESS;
}
