#ifndef SCAN_HEADER
#define SCAN_HEADER

#include "structures.h"
#include "tree.h"
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
char* catPath(char* dir,char* file);


/**
 * @brief
 *
 * @param path
 * @return s_file*
 */
char* getRelativePath(char* path);

#endif
