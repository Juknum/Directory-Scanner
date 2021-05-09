#ifndef SCAN_HEADER
#define SCAN_HEADER

#include <linux/limits.h>
#include <time.h>
#include <openssl/md5.h>
#include "structures.h"

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








#endif