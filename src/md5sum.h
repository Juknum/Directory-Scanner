#ifndef _MD5_H_
#define _MD5_H_
/**
 * @file md5sum.h
 * @author Florian Cloarec
 * @brief header file of the function in the md5sum part of the project
 * @version 0.1
 * @date 11 June 2021
 * 
 * @copyright GNU GENERAL PUBLIC LICENSE
 * 
 */

/**
 * @brief compute the md5sum of a file
 * 
 * @param path : the path of the file to compute
 * @param buffer : the buffer where the result is written
 * @return int : control value 1 if succes
 * @author Florian CLOAREC
 */
int compute_md5(char *path, unsigned char buffer[]);

#endif //_MD5_H_
