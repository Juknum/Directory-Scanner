#ifndef MD5SUM_HEADER
#define MD5SUM_HEADER


#include "structures.h"


/**
 * @brief 
 * 
 * @param path 
 * @param buffer 
 * @return int 
 */
int compute_md5(char *path, unsigned char buffer[]);

#endif