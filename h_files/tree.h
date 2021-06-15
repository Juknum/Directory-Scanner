#ifndef TREE_H
#define TREE_H


#include "structures.h"

int append_subdir(s_directory *child, s_directory *parent);

int append_file(s_file *child, s_directory *parent);

void clear_files(s_directory *parent);

void clear_subdirs(s_directory *parent);

#endif 
