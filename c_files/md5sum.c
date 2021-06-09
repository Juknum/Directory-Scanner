#include "../include/md5sum.h"

int compute_md5(char *path, unsigned char buffer[]){
    char sentence[512];
    ssize_t bytes;
    MD5_CTX current_char;
    FILE* f = NULL;

    f = fopen(path,"r");
    if(!f){
        fprintf(stderr,"This file does not exist !\n");
        return EXIT_FAILURE;
    }

    MD5_Init(&current_char);
    do
    {
        bytes=fread(sentence, 1, 512, f);
        MD5_Update(&current_char, sentence, bytes);
    }while(bytes > 0);
    
    for(int n=0; n<MD5_DIGEST_LENGTH; n++) printf("%02x", buffer[n]);
    MD5_Final(buffer, &current_char);

    return EXIT_SUCCESS;
}