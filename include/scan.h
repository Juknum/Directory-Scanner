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
 * @param path
 * @return s_file*
 */
char* catPath(char* dir,char* file);

/**
 * @brief
 *
 * @param path
 * @return s_file*
 */
s_file* insert_file(s_file* files,char* name);


/**
 * @brief
 *
 * @param path
 * @return s_file*
 */
s_directory* add_files(s_directory* dir,s_file* files);

/**
 * @brief
 *
 * @param path
 * @return s_file*
 */
s_directory* add_dir(s_directory* mainDir,s_directory* newDir);
#endif
