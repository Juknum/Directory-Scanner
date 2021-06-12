/**
 * @file scan.h
 * @author Blanchot Lukas, Viala Alexandre, Chaillard Léo, Lignon Thomas
 * @brief The functions used to scan the file in a certain file system are here.
 * @version 0.1
 * @date 2021-06-12
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef SCAN_HEADER
#define SCAN_HEADER

#include "structures.h"
#include "tree.h"
#include "md5sum.h"
typedef enum {FALSE,TRUE} Bool;

/**
 * @brief scan an entire directory and put the content of this directory in a s_directory structure.
 * 
 * @param path - string, complete path of the directory to scan.
 * @param md5 - bool, variable to know if the md5 must be calculated or not.
 * @return s_directory*, a linked list of s_directory.
 */
s_directory *process_dir(char *path, bool md5);

/**
 * @brief scan a file and put his content in a s_file strcture.
 * 
 * @param path - string, complete path of the file to scan.
 * @param md5 - bool, variable to know if the md5 must be calculated or not.
 * @return s_file*, a linked list of s_file.
 */
s_file *process_file(char *path, bool md5);


/**
 * @brief Concatenate in a dynamic allocated string the name of a dir and the name of a file.
 * 
 * @param dir - char*, the complete path of the directory
 * @param file - char*, the basename of the file.
 * @return char*, the complete name of the file.
 */
char* catPath(char* dir,char* file);


/**
 * @brief Get the relative path of a file or a directory according to its path (same behavior as basename).
 * 
 * @param path - char*, the complete path of the file.
 * @return char*, the basename of the the file.
 */
char* getRelativePath(char* path);

#endif
