#include <stdio.h>
#include <stdlib.h>
#include <bsd/md5.h>
#include <linux/limits.h>
#include <string.h>
#include <sys/types.h>

#ifndef _md5sum_H
#define _md5sum_H

/**
*@param path : path of the file to compute
*@param buffer : string to store the md5sum 
*@return -1 if it goes wrong, 0 otherwise
**/
int compute_md5sum(char* path, char buffer[]);

#endif