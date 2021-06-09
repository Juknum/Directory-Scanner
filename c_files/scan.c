#include "scan.h"

void scan(char *dir_name) {
	DIR *directory = opendir(dir_name);
	if (directory) {
		struct dirent *current_entry;
		struct stat current_stat;
		while ((current_entry = readdir(directory)) != NULL) {
			if (strcmp(current_entry->d_name, ".") == 0 || strcmp(current_entry->d_name, "..") == 0)
				continue;
			char new_path[MAX_HANDLED_PATH_LENGTH];
			if (snprintf(new_path, MAX_HANDLED_PATH_LENGTH, "%s/%s", dir_name, current_entry->d_name) < MAX_HANDLED_PATH_LENGTH) {
				if (lstat(new_path, &current_stat) != -1) {
					if (S_ISDIR(current_stat.st_mode)) {
						append_subdir(new_path,dir_name);
						scan(new_path);
						clear_subdirs(new_path);
					}else{
						append_file(new_path,dir_name);
						clear_files(new_path);
					}
				}
			}
		}
		closedir(directory);
	}else{
        free(directory);
    }
}