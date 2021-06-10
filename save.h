#ifndef _SAVE_H
#define _SAVE_H

#include "scan.h"
#include <stdbool.h>

bool do_arborescence = false;
bool do_path = false;
bool do_md5sum = false;

int save_to_file(s_directory *root, char *path_to_target);
void write_file_line(FILE *target_file,s_file *my_file,char *path,int depth);
void write_dir_line(FILE *target_file,s_directory* my_dir,char *path,int depth);

int save_to_file(s_directory *root, char *path_to_target, char *path_to_dir);
void print_dir(FILE *target_file, s_directory *my_dir, char *path, int depth);
void print_files(FILE *target_file, s_file *my_file, char *path, int depth);
void write_file_line(FILE *target_file,s_file *my_file, char *path,int depth);
void write_dir_line(FILE *target_file,s_directory* my_dir, char *path,int depth);


#endif