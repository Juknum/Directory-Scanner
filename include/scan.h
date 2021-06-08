#ifndef SCAN
#define SCAN

#define MAX_HANDLED_PATH_LENGTH 4096

#include "type.h"

void my_find(char *needle, char *haystack);

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