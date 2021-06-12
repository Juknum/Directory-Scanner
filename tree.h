#ifndef _TREE_H_
#define _TREE_H_

#include "types.h"

s_directory *get_last_dir(s_directory *dir);
s_file *get_last_file(s_file *f);

int append_subdir(s_directory *child, s_directory *parent);
int append_file(s_file *child, s_directory *parent);
void clear_files(s_directory *parent);
void clear_subdirs(s_directory *parent);

void clear_next_files(s_file *prev);
void clear_next_dirs(s_directory *prev);

#endif
