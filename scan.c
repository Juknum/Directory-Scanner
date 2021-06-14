#include "scan.h"
#include "tree.h"
#include "md5sum.h"

// Get the option from the main.c file
extern bool do_md5sum;

// stock directory's info in the memory
s_directory *process_dir(char* path){
	// Open the directory
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
	// Get the string after the last '/' 
	char* name = strrchr(path, '/');
	
	if(!name){
		// set the name to the path if there are no '/' in the string
		strcpy(my_dir->name, path);
	}else{
		// remove the '/' from the string
		name++;
		strcpy(my_dir->name, name);
	}
	struct stat stat_dir;
	// Get the stats of the directory
	if(stat(path, &stat_dir) == 0){
		my_dir->mod_time = stat_dir.st_mtime;
	}else{
		printf("Stat computing doesn't work on directory %s\n\n", path);
		fprintf(stderr, "Error while computing stats of %s\n", path);
		return NULL;
	}
	struct dirent* entry;
	// Read the entries of the directory
	while((entry = readdir(real_dir)) != NULL){
		// Don't read the "." and ".." files in order to avoid creating an infinite loop
		if(strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0){
			char full_path[PATH_MAX];
			// Concat directory path and name to get the file path
			sprintf(full_path, "%s/%s", path, entry->d_name);
			// Process then add to a list according to the type
			switch(entry->d_type){
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
			} 
		}  
	}
	return my_dir;
}

// Stock file's info into the memory
s_file *process_file(char *path){
	s_file* my_file = malloc(sizeof(s_file));
	// Get the string after the last '/' 
	char* name = strrchr(path, '/');
	if(!name){
		// set the name to the path if there are no '/' in the string
		strcpy(my_file->name, path);
	}else{
		// remove the '/' from the string
		name++;
		strcpy(my_file->name, name);
	}
	struct stat stat_file;
	// Get the stats of the directory
	if(stat(path, &stat_file) == 0){
		my_file->next_file=NULL;
		my_file->mod_time=stat_file.st_mtime;
		if(S_ISREG(stat_file.st_mode)){
			my_file->file_type=REGULAR_FILE;
			my_file->file_size=stat_file.st_size;
			// Compute md5sum if the option is activated
			if(do_md5sum){
				char *buffer = malloc(sizeof(char) * (strlen(path) + 34));
				if(compute_md5sum(path, buffer) != 0){
					printf("Error while computing md5sum of %s", my_file->name);
				}
				snprintf(my_file->md5sum, 32,"%s", buffer);
				printf("%s", my_file->md5sum);
				free(buffer);
			}			
		}else{
			my_file->file_type=OTHER_TYPE;
			my_file->md5sum[0]='\0';
			my_file->file_size = 0;
			if(S_ISLNK(stat_file.st_mode)){
				int name_size = FILENAME_MAX-strlen(my_file->name)-4;
				char pointed_file_name[name_size];
				// Get the pointed file if the file is a symbolic link
				if(readlink(path, pointed_file_name, name_size) != -1){
					// concat the pointed file name into the name string
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