#ifndef SAVE
#define SAVE

#include "type.h"

/*
 *  Function that recursively writes the content of every directory
 *  s_directory *root - structure containing all the data to use
 *  char *path_to_target - file where to write the data
 *  return - int, 0 if there is an error, else -1
 */
int save_to_file(s_directory *root, char *path_to_target);

/*
 *  Function that recursively writes the content of the file linked list of a directory
 *  s_directory *file - structure containing all the files of the directory
 *  char *path_to_target - file where to write the data
 *  return - int, 0 if there is an error, else -1
 */
int write_files(s_directory *file, char *path_to_target);

/*
 *  Function that recursively writes the content of the subdirectories linked list of a directory
 *  s_directory *directory - structure containing all the subdirectories
 *  char *path_to_target - file where to write the data
 *  return - int, 0 if there is an error, else -1
 */
int write_directories(s_directory *dir, char *path_to_target);

#endif