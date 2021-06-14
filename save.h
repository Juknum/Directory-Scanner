#include <stdbool.h>
#include <time.h>
#include <string.h>
#include <linux/limits.h>
#include "scan.h"

#ifndef _SAVE_H
#define _SAVE_H

/**
*@param root directory structure
*@param path_to_target path to the save file
*@param path_to_dir path to the analysed directory 
*@return -1 if it goes wrong, 0 otherwise
**/
int save_to_file(s_directory *root, char *path_to_target, char *path_to_dir);

/**
*@param target_file save file
*@param my_dir directory structure
*@param path path to the analysed directory 
*@param depth number of tabs to put before the line
*@return
**/
void print_dir(FILE *target_file, s_directory *my_dir, char *path, int depth);

/**
*@param target_file save file
*@param my_file file structure
*@param path path to the analysed file
*@param depth number of tabs to put before the line
*@return
**/
void print_files(FILE *target_file, s_file *my_file, char *path, int depth);

/**
*@param target_file save file
*@param my_dir file structure
*@param path path to the analysed file
*@param depth number of tabs to put before the line
*@return
**/
void write_file_line(FILE *target_file,s_file *my_file, char *path,int depth);

/**
*@param target_file save file
*@param my_dir directory structure
*@param path path to the analysed directory 
*@param depth number of tabs to put before the line
*@return
**/
void write_dir_line(FILE *target_file,s_directory* my_dir, char *path,int depth);

#endif