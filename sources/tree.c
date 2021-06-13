#include "../headers/tree.h"

void clear_files(s_file *parent){
	if(parent->next_file != NULL)	
		clear_files(parent->next_file);
	printf("liberation de %s\n", parent->name);
	free(parent);
}

void clear_subdirs(s_directory *parent){
	if(parent->files != NULL)	
		clear_files(parent->files);
	if(parent->subdirs != NULL)	
		clear_subdirs(parent->subdirs);
	if(parent->next_dir != NULL)	
		clear_subdirs(parent->next_dir);
	printf("liberation de %s\n", parent->name);
	free(parent);
}
