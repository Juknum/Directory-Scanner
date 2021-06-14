/**
 * @file tree.h
 * @author Blanchot Lukas, Viala Alexandre, Chaillard Léo, Lignon Thomas
 * @brief All the functions used to modify the s_directory & s_file structure are here.
 * @version 0.1
 * @date 2021-06-12
 *
 * @copyright Copyright (c) 2021
 *
 */

#ifndef TREE_HEADER
#define TREE_HEADER


#include "structures.h"


/**
 * @brief insert a new directory on front of the "parent" list.
 *
 * @param child new directory to be inserted as head.
 * @param parent current list of directories.
 * @return 1 if the directory can be properly inserted, 0 otherwise.
 */
int append_subdir(s_directory *child, s_directory *parent);

/**
 * @brief insert a new file on front of the files' linked list contained in the parent directory.
 *
 * @param child file to be inserted as head.
 * @param parent current directory in which to insert the child file.
 * @return 1 if the file can be properly inserted, 0 otherwise.
 */
int append_file(s_file *child, s_directory *parent);

/**
 * @brief clear the list of files contained in the parent directory.
 *
 * @param parent directory containing the list of files to be cleaned
 */
void clear_files(s_directory *parent);

/**
 * @brief clean recursively the entire content of the parent directory.
 *
 * @param parent directory to be cleaned.
 */
void clear_subdirs(s_directory *parent);



#endif
