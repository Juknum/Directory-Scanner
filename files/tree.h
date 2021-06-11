#ifndef TREE
#define TREE

#include "type.h"

/*
 *  Function that appends a subdirectory to a directory
 *  s_directory *child - directory child to append
 *  s_directory *parent - directory in which we append
 *  return - int, 0 if there is an error, else 1
 */
int append_subdir(s_directory *child, s_directory *parent);

/*
 *  Function that appends a file to a directory
 *  s_directory *child - directory child to append
 *  s_directory *parent - directory in which we append
 *  return - int, 0 if there is an error, else 1
 */
int append_file(s_file *child, s_directory *parent);

/*
 *  Function that clears the memory of the files
 *  s_directory *parent - pointer to clear
 */
void clear_files(s_directory *parent);

/*
 *  Function that recursivly removes the files from the memory
 *  s_directory *parent - file to clear
 */
void erase_file_data(s_file *parent);

/*
 *  Function that clears the memory of the subdirectories
 *  s_directory *parent - pointer to clear
 */
void clear_subdirs(s_directory *parent);

/*
 *  Function that recursivly removes the directories from the memory
 *  s_directory *parent - file to clear
 */
void erase_dir_data(s_directory *parent);

#endif