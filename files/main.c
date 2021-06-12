#include "type.h"
#include "tree.h"
#include "scan.h"
#include "save.h"
#include "md5sum.h"

int main(int argc, char *argv[]) {
	if (argc < 2) {
		printf("Please enter a Path name.\nOptions:\n-o + path: specify the save file.\n-s: also compute md5.\n-i + repertory path: specify the repertory to scan.\n");
		return 0;
	} 

	//strings to stock the optional paths
	char* save_file_path;
	char* directory;

	//variables linked to our options
	bool specific_save_file;
	bool md5_sum_computing;
	bool specific_directory;

	//initialize option variables
	specific_save_file = false;
	md5_sum_computing = false;
	specific_directory = false;

	//check the options
	int opt = 0;
    while((opt = getopt(argc, argv, "o:i:s")) != -1){
    	switch (opt){

    		case 'o': 
    			if (optarg[0] == '-'){
                    printf("Unavailable parameter! Please Don't enter an option as parameter of -o.\n");
                } else {
                	specific_save_file = true;
                	save_file_path = malloc(sizeof(char)*strlen(optarg));
                	strcpy(save_file_path,optarg);
                }
    			break;

    		case 's':
    			md5_sum_computing = true;
    			break;

    		case 'i': 
    			if (optarg[0] == '-'){
                    printf("Unavailable parameter! Please Don't enter an option as parameter of -i.\n");
                } else {
                	specific_directory = true;
                	directory = malloc(sizeof(char)*strlen(optarg));
                	strcpy(directory,optarg);
                }
    			break;
    	}
    }

    //TO DELETE for testing purposes
    if (md5_sum_computing == true){
    	printf("md5 ok");
    }

    //launch the program
	//scan(argv[1]);

	//free dynamically allowed variables
	if (specific_save_file){
		free (save_file_path);
	}
	if (specific_directory){
		free (directory);
	}

	return 0;
}