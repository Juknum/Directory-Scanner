#include "save.h"

int save_to_file(s_directory *root, char *path_to_target){
	if(root == NULL){
		printf("Directory structure couldn't be read!\n");
		return 0;
	}

	FILE *f = fopen(path_to_target, "w"); // Open in text mode, for writing
    if (!f){
    	printf("Could not open the save file!");
    	return 0;
    }

    //get a proper displayable date for the current directory
    char str_time[20];
    strftime(str_time, 20, "%Y-%m-%d %H:%M:%S", localtime(root.mod_time));

    //write in the save file all the expected data
	fprintf(f,"Directory:\n%d\t%s\t%s/\n",root.file_type,str_time,root.name);

	//display all files, not checking if the files pointer is null because it is done by the function already
	if(write_files(root.files,path_to_target) == 0){
		printf("No files!\n");
	}

	//display all subdirectories, similar to write_files
	if(write_directories(root.subdirs,path_to_target) == 0){
		printf("No subdirectories!\n");
	}

	printf("\n");
	//time to get recursive, we will first display all the data of subdirectories if there are some:
	if (root.subdirs != NULL){
		if (save_to_file(root.subdirs,path_to_target) == 0){
			fclose(f);
			return 0;
		}
	}

	//and now for the next directory of this level:
	if(root.next_dir != NULL){
		if (save_to_file(root.next_dir,path_to_target) == 0){
			fclose(f);
			return 0;
		}
	}

	fclose(f);
	return 1;
}

int write_files(s_directory *file, char *path_to_target){
	return 0;
}

int write_directories(s_directory *dir, char *path_to_target){
	return 0;
}