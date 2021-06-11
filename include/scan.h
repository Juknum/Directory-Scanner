#ifndef SCAN
#define SCAN

#include "type.h"
#include "tree.h"
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>

/*
 *  Function that recursivly reads directory and call s_directory *process_dir(char *path)
 *  to get information about directory or,s_file *process_file(char *path); to get 
 *  information about files.
 */
void scan(char *dir_name);

/*
 *  Function that will get a path to a directory and return a s_directoy variable, filled 
 *  with all the information about this directory.
 */
s_directory *process_dir(char *path);

/*
 *  Function that get a path to a file and return a s_file, filled with all the 
 *  information about this file.
 */
s_file *process_file(char *path);

#endif