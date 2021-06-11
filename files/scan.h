#ifndef SCAN
#define SCAN

#include "type.h"
#include "tree.h"
#include "md5sum.h"

void scan(char *dir_name);

/*
 *  Function that recursivly reads and get the informations of the repository
 *  char* path - string which represents the path to verify
 *  return - s_directory containing the informations of the directory
 */
s_directory *process_dir(char *path);

/*
 *  Function that recursivly reads and get the informations of the file
 *  char* path - string which represents the path to verify
 *  return - s_file containing the informations of the file
 */
s_file *process_file(char *path);

#endif