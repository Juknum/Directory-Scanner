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
 * @brief
 *
 * @param child
 * @param parent
 * @return int
 */
int append_subdir(s_directory *child, s_directory *parent);

/**
 * @brief
 *
 * @param child
 * @param parent
 * @return int
 */
int append_file(s_file *child, s_directory *parent);

/**
 * @brief
 *
 * @param parent
 */
void clear_files(s_directory *parent);

/**
 * @brief
 *
 * @param parent
 */
void clear_subdirs(s_directory *parent);



#endif 
