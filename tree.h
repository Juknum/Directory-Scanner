#include "scan.h"
#include <stdlib.h>

#ifndef _TREE_H
#define _TREE_H

int append_subdir(s_directory *child, s_directory *parent);
int append_file(s_file *child, s_directory *parent);
void clear_files(s_directory *parent);
void clear_subdirs(s_directory *parent);

#endif
