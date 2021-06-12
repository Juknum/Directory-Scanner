/**
 * @file save.h
 * @author Blanchot Lukas, Viala Alexandre, Chaillard Léo, Lignon Thomas
 * @brief All the functions linked to the save in a file is here.
 * @version 0.1
 * @date 2021-06-12
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef SAVE_HEADER
#define SAVE_HEADER

#include "structures.h"


/**
 * @brief Function to write the content of a s_directory (root).
 * 
 * @param root - s_directory, the content of a directory wrote inside the scan file.
 * @param path_to_target - string, the file to write in. If the value is "stdout", then it will write in the stdout.
 * @param md5 - bool, variable to know if the md5 must be read or not.
 * @return int - EXIT_SUCCESS if the function ran correctly.
 */
int save_to_file(s_directory *root, char *path_to_target, bool md5);

/**
 * @brief Recursive function to write the content of the files in a directory into the file fichier.
 * 
 * @param files - linked list of s_file, the list of files present in a certain directory.
 * @param fichier - FILE*, the file to write in the content of files.
 * @param tabs - int, the number of tabulations to print befor the content of a file.
 * @param md5 - bool, variable to know if the md5 must be written or not.
 */
void write_files(s_file* files,FILE* fichier, int tabs, bool md5);

/**
 * @brief Recursive function to write the content of a directory into the file fichier.
 * 
 * @param directories - linked list of s_directory, the list of directories present in a certain directory.
 * @param fichier - FILE*, the file to write in the content of files.
 * @param tabs - int, the number of tabulations to print befor the content of a file.
 * @param md5 - bool, variable to know if the md5 must be written or not.
 */
void write_directories(s_directory* directories, FILE* fichier, int tabs, bool md5);

/**
 * @brief Function to write tabulations inside the file fichier.
 * 
 * @param tabs - int, number of tabulations to print.
 * @param fichier - FILE*, the file to write in the tabulations.
 */
void print_tabs(int tabs,FILE* fichier);

/**
 * @brief Function to print the md5sum of a s_file which is not a s_directory.
 * 
 * @param buffer - u_char*, the md5sum of a certain file.
 * @param fichier - FILE*, the file to write in the md5sum.
 */
void print_md5sum(unsigned char buffer[], FILE* fichier);

#endif