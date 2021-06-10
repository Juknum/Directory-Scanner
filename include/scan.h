#ifndef SCAN_HEADER
#define SCAN_HEADER

#include "structures.h"
#include "tree.h"
#include "md5sum.h"
typedef enum {FALSE,TRUE} Bool;

/**
 * @brief
 *
 * @param path
 * @return s_directory*
 */
s_directory *process_dir(char *path, bool md5);

/**
 * @brief
 *
 * @param path
 * @return s_file*
 */
s_file *process_file(char *path, bool md5);


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
