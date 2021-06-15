/**
 * @file tree.h
 * @author Florian Cloarec
 * @brief header file of the function and struct in the tree part of the project
 * @version 0.1
 * @date 15 June 2021
 * 
 * @copyright GNU GENERAL PUBLIC LICENSE
 * 
 */

#ifndef _TREE_H
#define _TREE_H


/**
 * @brief add a element at the end of the link list of directory
 * 
 * @param child : the element to add
 * @param parent : the list to add it
 * @return int : control value
 * @author Florian CLOAREC
 */
int append_subdir(s_directory *child, s_directory *parent);

/**
 * @brief add an element at the end of the link list of file
 * 
 * @param child : the element to add
 * @param parent : the list to ad it
 * @return int : control value
 * @author Florian CLOAREC
 */
int append_file(s_file *child, s_directory *parent);

/**
 * @brief clear propely a whole link list of file
 * 
 * @param parent : the list to clear
 * @author Florian CLOAREC
 */
void clear_files(s_directory *parent);

/**
 * @brief clear propely a vhole link list of directory
 * 
 * @param parent : the list to clear
 * @author Florian CLOAREC
 */
void clear_subdirs(s_directory *parent);

/**
 * @brief free a s_file variable
 * 
 * @param file : the file to clear
 * @author Florian CLOAREC
 */
void free_s_file(s_file* file);


/**
 * @brief  free a s_directory variable
 * 
 * @param dir : the dir to clear
 * @author Florian CLOAREC
 */
void free_s_directory(s_directory* dir);

#endif
