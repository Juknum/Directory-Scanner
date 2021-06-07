#ifndef _SAVE_H
#define _SAVE_H

#include "scan.h"

int save_to_file(s_directory *root, char *path_to_target);
int save_to_db(s_directory *root);
void insert_files(s_directory* parent);
void insert_subdirs(s_directory* parent);
void write_files(s_directory* parent,int pos);
void write_subdirs(s_directory* parent,int pos);

#endif
