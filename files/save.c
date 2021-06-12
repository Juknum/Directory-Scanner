#include "save.h"

int save_to_file(s_directory *root, char *path_to_target, bool md5_sum_computing){
	if(root == NULL){
		printf("Directory structure couldn't be read!\n");
		return 0;
	}

	FILE *f = fopen(path_to_target, "a"); // Open in text mode, for writing
    if (!f){
    	printf("Could not open the save file!");
    	return 0;
    }

    //get a proper displayable date for the current directory
    char str_time[20];
    strftime(str_time, 20, "%Y-%m-%d %H:%M:%S", localtime(&root->mod_time));

    //write in the save file all the expected data
	fprintf(f,"Directory:\n0\t%s\t%s/\n",str_time,root->name);

	//display all files, not checking if the files pointer is null because it is done by the function already
	if(write_files(root->files,path_to_target,md5_sum_computing) == 0){
		printf("No files!\n");
	}

	//display all subdirectories, similar to write_files
	if(write_directories(root->subdirs,path_to_target) == 0){
		printf("No subdirectories!\n");
	}

	printf("\n");
	fclose(f);

	//time to get recursive, we will first display all the data of subdirectories if there are some:
	if (root->subdirs != NULL){
		if (save_to_file(root->subdirs,path_to_target, md5_sum_computing) == 0){
			return 0;
		}
	}

	//and now for the next directory of this level:
	if(root->next_dir != NULL){
		if (save_to_file(root->next_dir,path_to_target, md5_sum_computing) == 0){
			return 0;
		}
	}

	return -1;
}

int write_files(s_file *file, char *path_to_target, bool md5_sum_computing){
	if(file == NULL){
		return 0;
	}

	FILE *f = fopen(path_to_target, "a"); // Open in text mode, for writing
    if (!f){ //error should not happen at this point but still checking juuuuuuust in case you know
    	return 0;
    }

    //get a proper displayable date for the current directory
    char str_time[20];
    strftime(str_time, 20, "%Y-%m-%d %H:%M:%S", localtime(&file->mod_time));

    //write in the save file all the expected data
    fprintf(f,"%d\t%s\t",file->file_type,str_time);

    if(file->file_type == 1){
    	fprintf(f,"%ld\t",file->file_size);
    } 

    if(md5_sum_computing){
    	fprintf(f,"%s\t",file->md5sum);
    }

    fprintf(f,"%s\n",file->name);

	fclose (f);

	//recursively write all files in the linked list
	if(file->next_file != NULL){
		if(write_files(file->next_file,path_to_target, md5_sum_computing) == 0){
			return 0;
		}
	}

	return -1;
}

//similar code to save_to_file but without the files and double recursivity
int write_directories(s_directory *dir, char *path_to_target){
	if (dir == NULL){
		return 0;
	}

	FILE *f = fopen(path_to_target, "a"); // Open in text mode, for writing
    if (!f){ //error should not happen at this point but still checking juuuuuuust in case you know
    	return 0;
    }

    //get a proper displayable date for the current directory
    char str_time[20];
    strftime(str_time, 20, "%Y-%m-%d %H:%M:%S", localtime(&dir->mod_time));

    //write in the save file all the expected data
	fprintf(f,"0\t%s\t%s/\n",str_time,dir->name);

	fclose(f);

	//recursively write all subdirectories
	if(dir->next_dir != NULL){
		if (write_directories(dir->next_dir,path_to_target) == 0){
			return 0;
		}
	}

	return -1;
}