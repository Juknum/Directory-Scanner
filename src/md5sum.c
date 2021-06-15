/**
 * @file md5sum.c
 * @author Florian Cloarec
 * @brief source file that contain the implementation of the function in the md5sum part of the project
 * @version 0.1
 * @date 15 June 2021
 * 
 * @copyright GNU GENERAL PUBLIC LICENSE
 * 
 */

#include "include.h"

int compute_md5(char *path, unsigned char buffer[])
{

    //créer un md5
    FILE* f = fopen(path,"rb");
    MD5_CTX md5Context;
    int bytes;
    unsigned char data[1024];
    
    if(f==NULL){
    	printf("%s can't be opened",path);
    	return 0;
    }
    
    MD5_Init(&md5Context);
    while((bytes=fread(data,1,1024,f)) !=0)
    	MD5_Update(&md5Context,data,bytes);
    MD5_Final(buffer,&md5Context);
    
    fclose(f);
    
    return 1;
}
