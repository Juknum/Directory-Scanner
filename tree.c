#include "tree.h"

// Add a directory to the linked list
int append_subdir(s_directory *child, s_directory *parent){
    // Don't do anything if one of the elements is empty
    if(!parent || !child){
        return 0;
    } 
    // Set the subdirs list to the child element if it's empty
    if(!parent->subdirs){
        parent->subdirs = child;
        return 0;
    } 
    s_directory* temp_dir = parent->subdirs;
    // Go through the list until it reaches the last element
    while(temp_dir->next_dir){
        temp_dir = temp_dir->next_dir;
    } 
    // Add the directory to the list
    temp_dir->next_dir = child;
    return 0;
} 

// Add a file to the linked list
int append_file(s_file *child, s_directory *parent){
    // Don't do anything if one of the elements is empty
    if(!parent || !child){
        return 0;
    } 
    // Set the files list to the file list if it's empty
    if(!parent->files){
        parent->files = child;
        return 0;
    } 
    s_file* temp_file = parent->files;
     // Go through the list until it reaches the last element
    while(temp_file->next_file){
        temp_file = temp_file->next_file;
    } 
    // Add the file to the list
    temp_file->next_file = child;
    return 0;
}

// Free the memory occupied by a files list
void clear_files(s_directory *parent){
    if(!parent){
        return;
    } 
    if(!parent->files){
        return;
    } 
    s_file* temp_file = parent->files;
    s_file* next_temp_file;
    // Go through the list freeing the memory of the previous element
    while(temp_file->next_file){
        next_temp_file=temp_file->next_file;
        free(temp_file);
        temp_file = next_temp_file;
    }
    free(temp_file); 
}

// free the memory occupied by a directory list
void clear_subdirs(s_directory *parent){
    if(!parent){
        return;
    } 
    // Clear subdirectories if there are some
    if(parent->subdirs){
        clear_subdirs(parent->subdirs);
        
    } 
    // Clear files if there are some
    if(parent->files){
        clear_files(parent);
    }
    // Clear next file if there is one
    if(parent->next_dir){
        clear_subdirs(parent->next_dir);
    }
    free(parent);
}