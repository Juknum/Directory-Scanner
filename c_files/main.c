#include <stdio.h>
#include <stdlib.h>
#include "../include/save.h"
#include "../include/md5sum.h"
#include "../include/tree.h"
#include "../include/scan.h"



int main(int argc, char* argv[]){

    s_directory* test = process_dir(argv[1]);

    free(test);
    return EXIT_SUCCESS;
}
