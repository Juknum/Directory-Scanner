#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <stdint.h>
#include <unistd.h> 

#include "scan.h"

s_directory* process_dir(char* path){
	DIR* real_dir = opendir(path);
	if(!real_dir){
		printf("Directory %s couldn't be opened\n\n", path);
		fprintf(stderr, "Error while opening %s\n", path);
		return NULL;
	}
	s_directory* my_dir = malloc(sizeof(s_directory));
	my_dir->subdirs = NULL;
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
	if(stat(path, &stat_dir) == 0){
		my_dir->mod_time = stat_dir.st_mtime;
	}else{
		printf("Stat computing doesn't work on directory %s\n\n", path);
		fprintf(stderr, "Error while computing stats of %s\n", path);
		return NULL;
	}
	struct dirent* entry;
	while((entry = readdir(real_dir)) != NULL){
		if(strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0){
			char full_path[PATH_MAX];
			sprintf(full_path, "%s/%s", path, entry->d_name);
			/**switch(entry->d_type){
				case DT_DIR : 
					if(append_subdir(process_dir(full_path), my_dir) != 0){
						printf("Error while adding %s to %s\n\n", full_path, path);
						fprintf(stderr, "Error while adding %s to %s\n", full_path, path);
						return NULL;
					} 
				break;

				default :
					if(append_file(process_file(full_path), my_dir) != 0){
						printf("Error while adding %s to %s\n\n", full_path, path);
						fprintf(stderr, "Error while adding %s to %s\n", full_path, path);
						return NULL;
					} 
				break;
			} **/
		}  
	}
	return my_dir;
}

s_file *process_file(char *path){
	s_file* my_file = malloc(sizeof(s_file));

	char* name = strrchr(path, '/');
	if(!name){
		strcpy(my_file->name, path);
	}else{
		name++;
		strcpy(my_file->name, name);
	}
	struct stat stat_file;
	if(stat(path, &stat_file) == 0){
		my_file->next_file=NULL;
		my_file->mod_time=stat_file.st_mtime;
		if(S_ISREG(stat_file.st_mode)){
			my_file->file_type=REGULAR_FILE;
			my_file->file_size=stat_file.st_size;
			//compute_md5(path, my_file->md5sum);
		}else{
			my_file->file_type=OTHER_TYPE;
			my_file->md5sum[0]='\0';
			//my_file->file_size = NULL;
			if(S_ISLNK(stat_file.st_mode)){
				int name_size = FILENAME_MAX-strlen(my_file->name)-4;
				char pointed_file_name[name_size];
				if(readlink(path, pointed_file_name, name_size) != -1){
					strcat(my_file->name, " -> ");
					strcat(my_file->name, pointed_file_name);
				}else{
					printf("Error while following link %s\n\n", path);
					fprintf(stderr, "Error while following link %s\n", path);
					return NULL;
				} 
			}	
		} 
	}else{
		printf("Stat computing doesn't work on file %s\n\n", path);
		fprintf(stderr, "Error while computing stats of %s\n", path);
		return NULL;
	}
	return my_file;
} 