#ifndef MD5SUM_H
#define MD5SUM_H


#include "structures.h"


#define BUFFER_SIZE 16

int compute_md5(char *path, unsigned char buffer[]);

#endif
