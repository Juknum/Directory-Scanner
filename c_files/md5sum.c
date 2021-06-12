/**
 * @file md5sum.c
 * @author Blanchot Lukas, Viala Alexandre, Chaillard Léo, Lignon Thomas
 * @brief The functions used to compute the md5sum are here.
 * @version 0.1
 * @date 2021-06-12
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "../include/md5sum.h"

int compute_md5(char *path, unsigned char buffer[]){
    char* sentence = calloc(sizeof(char),512);
    ssize_t bytes;
    MD5_CTX current_char;
    FILE* f = NULL;
    struct stat buf;
    if(access(path, R_OK) !=0) return EXIT_FAILURE;
    if(stat(path, &buf) == -1) return EXIT_FAILURE;
    if( !S_ISLNK(buf.st_mode) && !S_ISREG(buf.st_mode)) return EXIT_FAILURE;
    f = fopen(path,"r");
    
    if(!f) return EXIT_FAILURE;

    MD5_Init(&current_char);
    do
    {
        bytes=fread(sentence, 1, 512, f);
        MD5_Update(&current_char, sentence, bytes);
    }while(bytes > 0);
    free(sentence);
    MD5_Final(buffer, &current_char);
    fclose(f);
    return EXIT_SUCCESS;
}

