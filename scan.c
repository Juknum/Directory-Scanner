#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <stdint.h>
#include "scan.h"

s_directory* process_dir(char* path){
	DIR* real_dir = opendir(path);
	if(!real_dir){
		printf("Directory %s couldn't be opened\n\n", path);
		fprintf(stderr, "Error while opening %s\n", path);
		exit(EXIT_FAILURE);
	}
	s_directory* my_dir = malloc(sizeof(s_directory));
	my_dir->sub_dirs = NULL;
	my_dir->next_dir = NULL;
	my_dir->files = NULL;
	char* name = strrchr(path, '/');
	if(!name){
		strcpy(my_dir->name, path);
	}else{
		name++;
		strcpy(my_dir->name, name);
	}
	struct stat stat_dir;
	if(stat(path, stat_dir) == 0){
		my_dir->mod_time = stat_dir.st_mtime;
	}else{
		printf("Stat computing doesn't work on directory %s\n\n", path);
		fprintf(stderr, "Error while computing stats of %s\n", path);
		exit(EXIT_FAILURE);
	}
	struct dirent* entry;
	while(entry = readdir(real_dir)) != NULL){
		if(strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0){
			char full_path[MAX_HANDLED_PATH_LENGTH];
			sprintf(full_path, "%s/%s", path, entry->d_name);
			switch(entry->d_name){
				case DT_DIR : 
					if(append_subdir(process_dir(full_path), my_dir) != 0){
						printf("Error while adding %s to %s\n\n", full_path, path);
						fprintf(stderr, "Error while adding %s to %s\n", full_path, path);
						exit(EXIT_FAILURE);
					} 
				break;
				
				case DT_REG :
					if(append_file(process_file(full_path, true), my_dir) != 0){
						printf("Error while adding %s to %s\n\n", full_path, path);
						fprintf(stderr, "Error while adding %s to %s\n", full_path, path);
						exit(EXIT_FAILURE);
					} 
				break;

				default :
					if(append_file(process_file(full_path, false), my_dir) != 0){
						printf("Error while adding %s to %s\n\n", full_path, path);
						fprintf(stderr, "Error while adding %s to %s\n", full_path, path);
						exit(EXIT_FAILURE);
					} 
				break;
			} 
		}  
	}
	return my_dir;
}

s_file *process_file(char *path, bool is_regular){
	s_directory* my_file = malloc(sizeof(s_file));

	char* name = strrchr(path, '/');
	if(!name){
		strcpy(my_file->name, path);
	}else{
		name++;
		strcpy(my_file->name, name);
	}
	struct stat stat_file;
	if(stat(path, stat_file) == 0){
		my_file->next_file=NULL;
		my_file->mod_time=file_stat.st_mtime;
		if(is_regular){
			my_file->file_type=REGULAR_FILE;
			my_file->file_size=file_stat.st_size;
			compute_md5(path, my_file->md5sum);
		}else{
			my_file->file_type=OTHER_TYPE;
			my_file->md5sum[0]='\0';
			my_file->size = NULL;
		} 
	}else{
		printf("Stat computing doesn't work on file %s\n\n", path);
		fprintf(stderr, "Error while computing stats of %s\n", path);
		exit(EXIT_FAILURE);
	}
} 