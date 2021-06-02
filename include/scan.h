#ifndef SCAN_HEADER
#define SCAN_HEADER

#include "structures.h"
typedef enum {FALSE,TRUE} Bool;

/**
 * @brief
 *
 * @param path
 * @return s_directory*
 */
s_directory *process_dir(char *path);

/**
 * @brief
 *
 * @param path
 * @return s_file*
 */
s_file *process_file(char *path);

/**
 * @brief 
 * 
 * @param givenPath 
 * @param fileName 
 * @return char* 
 */
char* catPath(char* givenPath,char* fileName);

/**
 * @brief
 *
 * @param path
 * @return s_file*
 */
s_file* insert_file(s_file* currFile,s_file* newFiles);


/**
 * @brief
 *
 * @param path
 * @return s_file*
 */
s_directory* add_files(s_directory* dir,s_file* files);
#endif
