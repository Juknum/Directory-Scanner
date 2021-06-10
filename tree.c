#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

int append_subdir(s_directory *child, s_directory *parent){
    if(!parent || !child){
        return 0;
    } 
    if(!parent->subdirs){
        parent->subdirs = child;
        return 0;
    } 
    s_directory* temp_dir = parent->subdirs;
    while(temp_dir->next_dir){
        temp_dir = temp_dir->next_dir;
    } 
    temp_dir->next_dir = child;
    return 0;
} 

int append_file(s_file *child, s_directory *parent){
    if(!parent || !child){
        return 0;
    } 
    if(!parent->files){
        parent->files = child;
        return 0;
    } 
    s_file* temp_file = parent->files;
    while(temp_file->next_file){
        temp_file = temp_file->next_file;
    } 
    temp_file->next_file = child;
    return 0;
}

void clear_files(s_directory *parent){
    if(!parent){
        return;
    } 
    if(!parent->files){
        return;
    } 
    s_file* temp_file = parent->files;
    s_file* next_temp_file;
    while(temp_file->next_file){
        next_temp_file=temp_file->next_file;
        free(temp_file);
        temp_file = next_temp_file;
    } 
}

void clear_subdirs(s_directory *parent){
    if(!parent){
        return;
    } 
    if(!parent->subdirs){
        return;
    } 
    s_directory* temp_dir = parent->subdirs;
    s_directory* next_temp_dir;
    while(temp_dir->next_dir){
        next_temp_dir=temp_dir->next_dir;
        clear_files(temp_dir);
        free(temp_dir);
        temp_dir = next_temp_dir;
    } 
}