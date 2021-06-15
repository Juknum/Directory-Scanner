/**
 * @file main.c
 * @author Florian Cloarec
 * @brief main file that contain the main fuction of the project
 * @version 0.1
 * @date 15 June 2021
 * 
 * @copyright GNU GENERAL PUBLIC LICENSE
 * 
 */

#include "include.h"

int main(int argc, char *argv[])
{
	int opt;
	char * dir_analyze = (char*)malloc(sizeof(char)*2);
	strcpy(dir_analyze, ".");

	char * save_file = (char*)malloc(sizeof(char)* 7);
	strcpy(save_file, "./save");

	bool md5 = false;
	while((opt=getopt(argc,argv,"i:so:")) != -1)
	{
		switch(opt)
		{
			case 'i':
				free(dir_analyze);
				dir_analyze = malloc(sizeof(char)*strlen(optarg)+1);
				strcpy(dir_analyze, optarg);
				dir_analyze = optarg;
				//printf("i : %s\n",dir_analyze);
				break;
			case 'o':
				free(save_file);
				save_file = malloc(sizeof(char)*strlen(optarg)+1);
				strcpy(save_file, optarg);
				//printf("o : %s\n",save_file);
				break;
			case 's': md5 = true;
                //printf("s\n");
				break;
		}
	}
	// No special output file path specified
	if(save_file == NULL){
	    // Check if output directory exists
        struct stat s;

        if (lstat(".filescanner/", &s) == -1) {
            if (mkdir(".filescanner/", 0777) == -1) {
                fprintf(stderr, "Couldn't create directory .filescanner!\n");
                return 1;
            }
        }
        save_file = generateFileName();
	}
    printf("*************program start*************\n");
	
    s_directory* dir;
    if (dir_analyze == NULL){
        dir = process_dir(".",md5);
    }
    else{
       dir = process_dir(dir_analyze,md5);
    }

	printf("%s\n",dir->name);
    // printf("%s\n", getFilePath("coucou", "/bin/src"));

    save_to_file(dir, save_file, dir_analyze);

    // Liberating memory
    free(save_file);

	printf("*************program stop*************\n");
    return 0;
}
