#include "scan.h"
#include <stdlib.h>

#ifndef _TREE_H
#define _TREE_H

/**
*@param child directory to add to the list
*@param parent parent directory
*@return -1 if it goes wrong, 0 otherwise
**/
int append_subdir(s_directory *child, s_directory *parent);

/**
*@param child file to add to the list
*@param parent parent directory
*@return -1 if it goes wrong, 0 otherwise
**/
int append_file(s_file *child, s_directory *parent);

/**
*@param parent directory to remove files from
*@return
**/
void clear_files(s_directory *parent);

/**
*@param parent directory to remove clear
*@return
**/
void clear_subdirs(s_directory *parent);

#endif
