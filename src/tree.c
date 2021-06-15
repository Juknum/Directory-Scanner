/**
 * @file tree.c
 * @brief source file that contain the implementation of the function in the tree part of the project
 * @version 0.1
 * @date 15 June 2021
 * 
 * @copyright GNU GENERAL PUBLIC LICENSE
 * 
 */

#include "include.h"

int append_subdir(s_directory *child, s_directory *parent)
{
	if(parent->subdirs == NULL){
		parent->subdirs = child;
	}
	else{
		s_directory * temp = parent->subdirs;
		while(temp->next_dir!=NULL){
			temp = temp->next_dir;
		}
		temp->next_dir = child;
	}
	
	
	if(parent->subdirs == NULL)return 0;
	else return 1;
}

int append_file(s_file *child, s_directory *parent)
{
	if(parent->files == NULL){
		parent->files = child;
	}
	else{
		s_file * temp = parent->files;
		while(temp->next_file!=NULL){
			temp = temp->next_file;
		}
		temp->next_file = child;
	}
	if(parent->files == NULL)return 0;
	else return 1;
}

void clear_files(s_directory *parent)
{
	s_file *temp = parent->files;
	s_file *temp1 = NULL;
	while(temp != NULL){
		temp1 = temp->next_file;
		free_s_file(temp);
		temp = temp1;
	}
}

void clear_subdirs(s_directory *parent)
{
	s_directory *temp = parent->subdirs;
	s_directory *temp1 = NULL;
	
	while(temp != NULL){
		if(temp->subdirs != NULL)clear_subdirs(temp);
		if(temp->files != NULL)clear_files(temp);
		temp1 = temp->next_dir;
		free_s_directory(temp);
		temp = temp1;
	}
}

void free_s_file(s_file* file){
    free(file->name);
    free(file->md5sum);
    free(file);
}

void free_s_directory(s_directory* dir){
    free(dir->name);
    free(dir);
}
