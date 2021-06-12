/**
 * @file md5sum.h
 * @author Blanchot Lukas, Viala Alexandre, Chaillard Léo, Lignon Thomas
 * @brief The functions used to compute the md5sum are here.
 * @version 0.1
 * @date 2021-06-12
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef MD5SUM_HEADER
#define MD5SUM_HEADER


#include "structures.h"
#include <openssl/md5.h>


/**
 * @brief Function to compute the md5 sum of file. If the file is not accessible or if it is not a classic file, the md5sum will not be read.
 * 
 * @param path - string, the complete path of the file.
 * @param buffer - u_char*, the place where the md5sum will be saved.
 * @return int - EXIT_SUCCESS if the md5sum has been calculated. EXIT_FAILURE else.
 */
int compute_md5(char *path, unsigned char buffer[]);



#endif