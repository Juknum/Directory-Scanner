#include "../include/md5sum.h"

int compute_md5(char *path, unsigned char buffer[]){
    int ch_buffer;
    unsigned char* sentence = NULL;
    int size = 0;;
    FILE* f = NULL;

    f = fopen(path,"r");
    if(!f){
        fprintf(stderr,"This file does not exist !\n");
        return EXIT_FAILURE;
    }

    do{
        ch_buffer = fgetc(f);
        if(ch_buffer != EOF){
            if(size == 0){
                sentence = malloc(sizeof(char)*1);
            } else {
                sentence = realloc(sentence, sizeof(char)*(size+1));
            }
            
            if(ch_buffer == '\n'){
                sentence[size] = '\0';
            } else {
                sentence[size]= ch_buffer;
            }
            size++;
        }
    } while(ch_buffer != EOF);
    size++;
    buffer = MD5(sentence,size,buffer);

    return EXIT_SUCCESS;
}