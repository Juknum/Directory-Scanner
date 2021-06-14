#include "md5sum.h"


//Compute the md5sum of a file manually using openssl or bsd library
/**int compute_md5sum(char *path, unsigned char buffer[]){
    // Reads the file in binary mode
    FILE *file=fopen(path,"rb");
    if(!file){
        printf("File %s couldn't be opened\n\n", path);
        fprintf(stderr, "Error while opening %s", path);
        return -1;
    }
	uint8_t temp_buffer[512];
	ssize_t bytes;
    MD5_CTX ctx;
    // Initialize the structure used for md5sum computing
	CC_MD5_Init(&ctx);
    // read the file 512 bytes at a time
	while((bytes=fread(temp_buffer, 1, 512, file)) > 0){
		// Add the 512 bytes part of the file to the total md5sum 
        CC_MD5_Update(&ctx, temp_buffer, bytes);
    }
    // End the md5sum computation and stock the result in the buffer
	CC_MD5_Final(buffer, &ctx);
	fclose(file);
    return 0;
}**/

//compute the md5sum of a file using a bash command
int compute_md5sum(char *path, char buffer[]){
    char *command_line= malloc(sizeof(char)*(strlen(path)+8));
    char *temp_buffer= malloc(sizeof(char)*(strlen(path)+34));
    // Write the command line to send to the terminal
    sprintf(command_line, "md5sum %s", path);
    // Sends the command to the terminal
    FILE *system_stream = popen(command_line, "r");   
    if(!system_stream){
        free(command_line);
        free(temp_buffer);
        return -1;
    }
    // Reads the content of the system stream while there is content
    while(fgets(buffer,PATH_MAX+33, system_stream) != 0){ ; }
    strcpy(buffer, temp_buffer);
    free(temp_buffer);
    free(command_line);
    if(pclose(system_stream) == -1){
        printf("Error while closing file stream\n");
        return -1;
    }
    return 0;
}
    