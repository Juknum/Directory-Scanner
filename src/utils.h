#ifndef _UTILS_H_
#define _UTILS_H_

/**
 * @file utils.h
 * @author Florian Cloarec
 * @brief header file of the function and struct who can be util for all part of the project
 * @version 0.1
 * @date 07 June 2021
 * 
 * @copyright GNU GENERAL PUBLIC LICENSE
 * 
 */


/**
 * @brief Get the File Path object
 * 
 * @param fileName : the name of the file
 * @param dirPath : the path of the file
 * @return char* : the pointer on the created string
 * @author Florian CLOAREC
 */
char* getFilePath(char* fileName, char* dirPath);

/**
 * @brief Get the File Name object
 * 
 * @param path : the name of the file
 * @return char* : the pointer on the created string
 * @author Florian CLOAREC
 */
char* getFileName(char* path);


#endif //_UTILS_H_